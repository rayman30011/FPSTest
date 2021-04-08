// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/WeaponComponent.h"
#include "Weapon/BaseWeapon.h"
#include <GameFramework/Character.h>

UWeaponComponent::UWeaponComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UWeaponComponent::BeginPlay()
{
    Super::BeginPlay();

    SpawnWeapon();
}

void UWeaponComponent::SpawnWeapon()
{
    if (!GetWorld()) return;

    CurrentWeapon = GetWorld()->SpawnActor<ABaseWeapon>(WeaponClass);
    if (!CurrentWeapon) return;

    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character) return;

    FAttachmentTransformRules Rules(EAttachmentRule::SnapToTarget, false);
    CurrentWeapon->AttachToComponent(Character->GetMesh(), Rules, SocketName);
    CurrentWeapon->SetOwner(GetOwner());
}

void UWeaponComponent::Fire() {
    if (!CurrentWeapon) return;
    CurrentWeapon->Fire();
}
