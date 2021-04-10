// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon/BaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeapon, All, All);

ABaseWeapon::ABaseWeapon()
{
    PrimaryActorTick.bCanEverTick = false;

    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
    SetRootComponent(WeaponMesh);
}

void ABaseWeapon::BeginPlay()
{
    Super::BeginPlay();
    
    check(WeaponMesh);
    CurrentAmmo = DefaultAmmo;
}

void ABaseWeapon::StartFire()
{
}

void ABaseWeapon::StopFire()
{
}

void ABaseWeapon::MakeShoot()
{
}

APlayerController* ABaseWeapon::GetPlayerController() const
{
    const auto Player = Cast<ACharacter>(GetOwner());
    if (!Player) return nullptr;

    return Player->GetController<APlayerController>();
}

bool ABaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
    const auto Controller = GetPlayerController();
    if (!Controller) return false;

    Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
    return true;
}

bool ABaseWeapon::GetTraceData(FVector& Start, FVector& End) const
{
    FVector ViewLocation;
    FRotator ViewRotation;
    if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

    Start = ViewLocation;
    const FVector ShootDirection = ViewRotation.Vector();
    End = Start + ShootDirection * TranceLength;

    return true;
}

FVector ABaseWeapon::GetMuzzleLocation() const
{
    return WeaponMesh->GetSocketTransform(MuzzleSocketName).GetLocation();
}

void ABaseWeapon::DecreaseAmmo()
{
    CurrentAmmo.Bullets--;
    LogAmmo();
    if (IsClipEmpty() && !IsEmptyAmmo())
    {
        ChangeClip();
    }
}

bool ABaseWeapon::IsEmptyAmmo() const
{
    return !CurrentAmmo.Infinite && CurrentAmmo.Clips <= 0 && IsClipEmpty();
}

bool ABaseWeapon::IsClipEmpty() const
{
    return CurrentAmmo.Bullets <= 0;
}

void ABaseWeapon::ChangeClip()
{
    UE_LOG(LogWeapon, Display, TEXT("---- Change Clip ----"));
    
    CurrentAmmo.Bullets = DefaultAmmo.Bullets;
    CurrentAmmo.Clips--;
}

void ABaseWeapon::LogAmmo()
{
    FString LogMessage = "Ammo: " + FString::FromInt(CurrentAmmo.Bullets) + "/";
    LogMessage += CurrentAmmo.Infinite ? "Inf" : FString::FromInt(CurrentAmmo.Clips);
    UE_LOG(LogWeapon, Display, TEXT("%s"), *LogMessage);
}
