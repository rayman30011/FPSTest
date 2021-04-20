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
    checkf(DefaultAmmo.Bullets > 0, TEXT("Bullets count couldn't be less or equal 0"));
    checkf(DefaultAmmo.Clips > 0, TEXT("Clips count couldn't be less or equal 0"));
    
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
    const auto Character = Cast<ACharacter>(GetOwner());
    if (!Character) return false;

    if (Character->IsPlayerControlled())
    {
        const auto Controller = GetPlayerController();
        if (!Controller) return false;

        Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
        return true;
    }

    ViewLocation = GetMuzzleLocation();
    ViewRotation = WeaponMesh->GetSocketRotation(MuzzleSocketName);
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
    if (IsClipEmpty())
    {
        UE_LOG(LogWeapon, Warning, TEXT("Clip is Empty"));
        return;
    }
    
    CurrentAmmo.Bullets--;
    LogAmmo();
    if (IsClipEmpty() && !IsEmptyAmmo())
    {
        StopFire();
        OnClipEmpty.Broadcast(this);
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

bool ABaseWeapon::IsAmmoFull() const
{
    return CurrentAmmo.Clips == DefaultAmmo.Clips && CurrentAmmo.Bullets == DefaultAmmo.Bullets;
}

void ABaseWeapon::ChangeClip()
{
    UE_LOG(LogWeapon, Display, TEXT("---- Change Clip ----"));

    if (!CurrentAmmo.Infinite)
    {
        if (CurrentAmmo.Clips <= 0)
        {
            UE_LOG(LogWeapon, Warning, TEXT("No more clips"));
            return;
        }
        CurrentAmmo.Clips--;
    }
    
    CurrentAmmo.Bullets = DefaultAmmo.Bullets;
}

bool ABaseWeapon::CanReload() const
{
    return CurrentAmmo.Bullets < DefaultAmmo.Bullets && CurrentAmmo.Clips > 0;
}

bool ABaseWeapon::TryToAddClips(int32 ClipsAmount)
{
    if (CurrentAmmo.Infinite || IsAmmoFull() || ClipsAmount <= 0) return false;

    if (IsEmptyAmmo())
    {
        UE_LOG(LogWeapon, Warning, TEXT("Ammo is empty"));
        CurrentAmmo.Clips = FMath::Clamp(CurrentAmmo.Clips + ClipsAmount, 0, DefaultAmmo.Clips + 1);
        OnClipEmpty.Broadcast(this);
    }
    else if (CurrentAmmo.Clips < DefaultAmmo.Clips)
    {
        const auto NextClipsAmount = CurrentAmmo.Clips + ClipsAmount;
        if (DefaultAmmo.Clips - NextClipsAmount >= 0)
        {
            CurrentAmmo.Clips = NextClipsAmount;
            UE_LOG(LogWeapon, Warning, TEXT("Clips added"));
        }
        else
        {
            CurrentAmmo.Clips = DefaultAmmo.Clips;
            CurrentAmmo.Bullets = DefaultAmmo.Bullets;
            UE_LOG(LogWeapon, Warning, TEXT("Ammo is full"));
        }
    }
    else
    {
        CurrentAmmo.Bullets = DefaultAmmo.Bullets;
        UE_LOG(LogWeapon, Warning, TEXT("Bullets is full"));
    }

    return true;
}

void ABaseWeapon::LogAmmo()
{
    FString LogMessage = "Ammo: " + FString::FromInt(CurrentAmmo.Bullets) + "/";
    LogMessage += CurrentAmmo.Infinite ? "Inf" : FString::FromInt(CurrentAmmo.Clips);
    UE_LOG(LogWeapon, Display, TEXT("%s"), *LogMessage);
}
