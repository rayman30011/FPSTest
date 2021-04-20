// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/PlayerCharacter.h"
#include "AIPlayerCharacter.generated.h"

class UBehaviorTree;

UCLASS()
class TESTFPS_API AAIPlayerCharacter : public APlayerCharacter
{
    GENERATED_BODY()
    
public:
    AAIPlayerCharacter(const FObjectInitializer& ObjectInitializer);

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
    UBehaviorTree* BehaviorTree;
};
