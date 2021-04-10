// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/LauncherWeapon.h"
#include "Weapon/Projectile.h"

void ALauncherWeapon::StartFire()
{
    MakeShoot();
}

void ALauncherWeapon::MakeShoot()
{
    if (!GetWorld()) return;
    
    FVector TraceStart, TraceEnd;
    if (!GetTraceData(TraceStart, TraceEnd)) return;

    FCollisionQueryParams Params;
    Params.AddIgnoredActor(GetOwner());
    FHitResult HitResult;
    GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, Params);

    const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
    const FVector Direction = (EndPoint - GetMuzzleLocation()).GetSafeNormal();

    const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleLocation());
    AProjectile* Projectile = GetWorld()->SpawnActorDeferred<AProjectile>(ProjectileClass, SpawnTransform);
    if (Projectile)
    {
        Projectile->SetShootDirection(Direction);
        Projectile->SetOwner(GetOwner());
        Projectile->FinishSpawning(SpawnTransform);
    }
}