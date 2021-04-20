// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AIPlayerCharacter.h"


#include "AIWeaponComponent.h"
#include "AI/CharacterAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

AAIPlayerCharacter::AAIPlayerCharacter(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<UAIWeaponComponent>("WeaponComponent"))
{
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    AIControllerClass = ACharacterAIController::StaticClass();
    bUseControllerRotationYaw = false;
    if (GetCharacterMovement())
    {
        GetCharacterMovement()->bUseControllerDesiredRotation = true;
        GetCharacterMovement()->RotationRate = FRotator(0.f, 360.f, 0.f);
    }
}
