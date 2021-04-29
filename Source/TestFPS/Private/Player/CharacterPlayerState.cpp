// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/CharacterPlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogCharacterState, All, All);

void ACharacterPlayerState::LogInfo()
{
    UE_LOG(LogCharacterState, Display, TEXT("Team %d, Kills %d, Deaths %d"), TeamID, KillsCount, DeathCount);
}
