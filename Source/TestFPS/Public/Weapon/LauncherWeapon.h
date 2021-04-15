// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/BaseWeapon.h"
#include "LauncherWeapon.generated.h"

class UWeaponFXComponent;
class AProjectile;

UCLASS()
class TESTFPS_API ALauncherWeapon : public ABaseWeapon
{
    GENERATED_BODY()

public:
    ALauncherWeapon();

    virtual void BeginPlay() override;
    
    virtual void StartFire() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    TSubclassOf<AProjectile> ProjectileClass;

    UPROPERTY(VisibleAnywhere, Category = "FX")
    UWeaponFXComponent* WeaponFXComponent;

    virtual void MakeShoot() override;
};
