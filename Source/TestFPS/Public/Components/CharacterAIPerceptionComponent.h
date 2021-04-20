// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "CharacterAIPerceptionComponent.generated.h"

/**
 * 
 */
UCLASS()
class TESTFPS_API UCharacterAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()

public:
    AActor* GetClosesEnemy() const;
};
