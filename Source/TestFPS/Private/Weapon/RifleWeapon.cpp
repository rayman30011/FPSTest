// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/RifleWeapon.h"

#include "DrawDebugHelpers.h"
#include "Weapon/Components/WeaponFXComponent.h"

ARifleWeapon::ARifleWeapon()
{
    WeaponFXComponent = CreateDefaultSubobject<UWeaponFXComponent>("WeaponFXComponent");
}

void ARifleWeapon::BeginPlay()
{
    Super::BeginPlay();
    check(WeaponFXComponent);
}

void ARifleWeapon::StartFire()
{
    GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ARifleWeapon::MakeShoot, TimeBetweenShot, true);
    MakeShoot();
}

void ARifleWeapon::StopFire()
{
    GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}

void ARifleWeapon::MakeShoot()
{
    if (!GetWorld() || IsEmptyAmmo())
    {
        StopFire();
        return;
    }

    FVector TraceStart, TraceEnd;
    if (!GetTraceData(TraceStart, TraceEnd))
    {
        StopFire();
        return;
    }

    FCollisionQueryParams Params;
    Params.AddIgnoredActor(GetOwner());
    Params.bReturnPhysicalMaterial = true;
    FHitResult HitResult;
    GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, Params);

    if (HitResult.bBlockingHit)
    {
        WeaponFXComponent->PlayImpactFX(HitResult);

        const auto DamagedActor = HitResult.Actor;
        if (DamagedActor.IsValid())
        {
            HitResult.Actor->TakeDamage(Damage, FDamageEvent{}, GetPlayerController(), this);
        }
    }
    DecreaseAmmo();
    OnShot.Broadcast(GetCurrentAmmo());
}

bool ARifleWeapon::GetTraceData(FVector& Start, FVector& End) const
{
    FVector ViewLocation;
    FRotator ViewRotation;
    if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

    Start = ViewLocation;
    const auto HalfRad = FMath::DegreesToRadians(BulletSpreed);
    const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad);
    End = Start + ShootDirection * TranceLength;

    return true;
}