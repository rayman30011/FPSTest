// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "NextLocationTask.generated.h"

UCLASS()
class TESTFPS_API UNextLocationTask : public UBTTaskNode
{
    GENERATED_BODY()

public:
    UNextLocationTask();

    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float Radius = 1000.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    bool SelfCenter = true;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector LocationKey;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (EditCondition = "!SelfCenter"))
    FBlackboardKeySelector CenterActorKey;
};
