// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterGameModeBase.h"

#include "Player/PlayerCharacter.h"
#include "UI/GameHUD.h"

AShooterGameModeBase::AShooterGameModeBase()
{
    DefaultPawnClass = APlayerCharacter::StaticClass();
    PlayerControllerClass = APlayerController::StaticClass();
    HUDClass = AGameHUD::StaticClass();
}