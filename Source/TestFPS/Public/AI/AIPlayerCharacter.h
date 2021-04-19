// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/PlayerCharacter.h"
#include "AIPlayerCharacter.generated.h"

UCLASS()
class TESTFPS_API AAIPlayerCharacter : public APlayerCharacter
{
    GENERATED_BODY()
    
public:
    AAIPlayerCharacter(const FObjectInitializer& ObjectInitializer);
};
