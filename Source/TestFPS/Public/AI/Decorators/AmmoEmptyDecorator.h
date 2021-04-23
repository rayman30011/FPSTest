// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"

#include "AmmoEmptyDecorator.generated.h"


class ABaseWeapon;

UCLASS()
class TESTFPS_API UAmmoEmptyDecorator : public UBTDecorator
{
    GENERATED_BODY()
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    TSubclassOf<ABaseWeapon> WeaponClass;

    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
