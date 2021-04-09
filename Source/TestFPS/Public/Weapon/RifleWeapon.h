// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/BaseWeapon.h"
#include "RifleWeapon.generated.h"

/**
 * 
 */
UCLASS()
class TESTFPS_API ARifleWeapon : public ABaseWeapon
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float TimeBetweenShot = 0.2;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float BulletSpreed = 3.f;
    
    virtual void StartFire() override;
    virtual void StopFire() override;
    virtual bool GetTraceData(FVector &Start, FVector &End) const override;

protected:
    virtual void MakeShoot() override;

private:
    FTimerHandle ShotTimerHandle;
};
