// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AIPlayerCharacter.h"

#include "AI/CharacterAIController.h"

AAIPlayerCharacter::AAIPlayerCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    AIControllerClass = ACharacterAIController::StaticClass();
}
