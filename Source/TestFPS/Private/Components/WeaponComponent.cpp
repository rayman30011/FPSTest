// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/WeaponComponent.h"
#include "Weapon/BaseWeapon.h"
#include "GameFramework/Character.h"
#include "Animations/EquipRifleAnimNotify.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All);

UWeaponComponent::UWeaponComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UWeaponComponent::BeginPlay()
{
    Super::BeginPlay();

    CurrentWeaponIndex = 0;
    InitAnimations();
    SpawnWeapons();
    EquipWeapon(CurrentWeaponIndex);
}

void UWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    CurrentWeapon = nullptr;
    for (auto Weapon : AvailableWeapons)
    {
        Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
        Weapon->Destroy();
    }

    AvailableWeapons.Empty();
    Super::EndPlay(EndPlayReason);
}

void UWeaponComponent::EquipWeapon(int32 Index)
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character) return;

    if (CurrentWeapon)
    {
        CurrentWeapon->StopFire();
        AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), ArmorySocketName);
    }

    CurrentWeapon = AvailableWeapons[Index];
    AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), EquipSocketName);
    EquipAnimInProgress = true;
    PlayAnimMontage(EquipAnimMontage);
}

void UWeaponComponent::SpawnWeapons()
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character || !GetWorld()) return;

    for (auto WeaponClass : WeaponClasses)
    {
        auto Weapon = GetWorld()->SpawnActor<ABaseWeapon>(WeaponClass);
        if (!Weapon) continue;

        Weapon->SetOwner(GetOwner());
        AvailableWeapons.Add(Weapon);

        AttachWeaponToSocket(Weapon, Character->GetMesh(), ArmorySocketName);
    }
}

void UWeaponComponent::AttachWeaponToSocket(ABaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName)
{
    if (!Weapon || !SceneComponent) return;

    const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
    Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}

void UWeaponComponent::StartFire()
{
    if (!CanFire()) return;
    CurrentWeapon->StartFire();
}

void UWeaponComponent::StopFire()
{
    if (!CurrentWeapon) return;
    CurrentWeapon->StopFire();
}

void UWeaponComponent::NextWeapon()
{
    if (!CanEquip()) return;
    
    CurrentWeaponIndex = (CurrentWeaponIndex + 1) % AvailableWeapons.Num();
    EquipWeapon(CurrentWeaponIndex);
}

void UWeaponComponent::PlayAnimMontage(UAnimMontage* Animation)
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character || !GetWorld()) return;

    Character->PlayAnimMontage(Animation);
}

void UWeaponComponent::InitAnimations()
{
    if (!EquipAnimMontage) return;
    
    const auto NotifyEvents = EquipAnimMontage->Notifies;
    for (auto NotifyEvent : NotifyEvents)
    {
        auto EquipFinishNotify = Cast<UEquipRifleAnimNotify>(NotifyEvent.Notify);
        if (!EquipFinishNotify) continue;

        EquipFinishNotify->OnNotified.AddUObject(this, &UWeaponComponent::OnEquipFinished);
        break;
    }
}

void UWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComp)
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character || Character->GetMesh() != MeshComp) return;

    EquipAnimInProgress = false;
}

bool UWeaponComponent::CanFire() const
{
    return CurrentWeapon && !EquipAnimInProgress;
}

bool UWeaponComponent::CanEquip() const
{
    return !EquipAnimInProgress;
}
