// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Weapon/BaseWeapon.h"
#include "RifleWeapon.generated.h"

class UWeaponFXComponent;
class UNiagaraSystem;

UCLASS()
class TESTFPS_API ARifleWeapon : public ABaseWeapon
{
    GENERATED_BODY()

public:
    ARifleWeapon();
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float TimeBetweenShot = 0.2;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float BulletSpreed = 3.f;

    UPROPERTY(VisibleAnywhere, Category = "FX")
    UWeaponFXComponent* WeaponFXComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FX")
    UNiagaraSystem* TraceFX;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FX")
    FString TraceTargetName = "TraceTarget";

    virtual void BeginPlay() override;
    virtual void StartFire() override;
    virtual void StopFire() override;
    virtual bool GetTraceData(FVector &Start, FVector &End) const override;

protected:
    virtual void MakeShoot() override;

private:
    FTimerHandle ShotTimerHandle;

    void SpawnTraceFX(const FVector& Start, const FVector& End);
    AController* GetController() const;
};
