// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/BasePickup.h"

#include "AmmoPackPickup.generated.h"

class ABaseWeapon;

UCLASS()
class TESTFPS_API AAmmoPackPickup : public ABasePickup
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1.0", ClampMax = "10.0"))
    int32 ClipsAmount = 2;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
    TSubclassOf<ABaseWeapon> WeaponClass;

    virtual bool GivePickupTo(APawn* Pawn) override;
};
