// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CustomCharacterMovementComponent.h"
#include <Player/PlayerCharacter.h>

float UCustomCharacterMovementComponent::GetMaxSpeed() const
{
    const float MaxSpeed = Super::GetMaxSpeed();
    const APlayerCharacter* Player = Cast<APlayerCharacter>(GetPawnOwner());
    return Player && Player->IsRunning() ? MaxSpeed * RunModifier : MaxSpeed;
}