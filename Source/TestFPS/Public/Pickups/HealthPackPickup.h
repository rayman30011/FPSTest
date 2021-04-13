// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/BasePickup.h"
#include "HealthPackPickup.generated.h"

/**
 * 
 */
UCLASS()
class TESTFPS_API AHealthPackPickup : public ABasePickup
{
	GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1.0"))
    float HealthAmount = 100.f;

    virtual bool GivePickupTo(APawn* Pawn) override;
};
