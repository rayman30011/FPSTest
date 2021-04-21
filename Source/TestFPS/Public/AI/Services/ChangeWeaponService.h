// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "ChangeWeaponService.generated.h"


UCLASS()
class TESTFPS_API UChangeWeaponService : public UBTService
{
    GENERATED_BODY()

public:
    UChangeWeaponService();
    

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (ClampMin = "0", ClampMax = "1"))
    float Priority;

    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
