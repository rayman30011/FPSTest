// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/RifleWeapon.h"

#include "DrawDebugHelpers.h"

void ARifleWeapon::StartFire()
{
    MakeShoot();
    GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ARifleWeapon::MakeShoot, TimeBetweenShot, true);
}

void ARifleWeapon::StopFire()
{
    MakeShoot();
    GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}

void ARifleWeapon::MakeShoot()
{
    if (!GetWorld()) return;

    FVector TraceStart, TraceEnd;
    if (!GetTraceData(TraceStart, TraceEnd)) return;

    FCollisionQueryParams Params;
    Params.AddIgnoredActor(GetOwner());
    FHitResult HitResult;
    GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, Params);

    if (HitResult.bBlockingHit)
    {
        DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10, 24, FColor::Red, false, 3.f);
        DrawDebugLine(GetWorld(), GetMuzzleLocation() , HitResult.ImpactPoint, FColor::Red, false, 1.f, 0, 3.f);

        const auto DamagedActor = HitResult.Actor;
        if (DamagedActor.IsValid())
        {
            HitResult.Actor->TakeDamage(Damage, FDamageEvent{}, GetPlayerController(), this);
        }
    }
    else
    {
        DrawDebugLine(GetWorld(), GetMuzzleLocation() , TraceEnd, FColor::Red, false, 1.f, 0, 3.f);
    }
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