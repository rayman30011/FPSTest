// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterGameModeBase.h"


#include "AIController.h"
#include "Player/PlayerCharacter.h"
#include "UI/GameHUD.h"

AShooterGameModeBase::AShooterGameModeBase()
{
    DefaultPawnClass = APlayerCharacter::StaticClass();
    PlayerControllerClass = APlayerController::StaticClass();
    HUDClass = AGameHUD::StaticClass();
}

void AShooterGameModeBase::StartPlay()
{
    Super::StartPlay();

    SpawnBots();
}

UClass* AShooterGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
    if (InController && InController->IsA<AAIController>())
    {
        return CharacterClass;
    }

    return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void AShooterGameModeBase::SpawnBots()
{
    if (!GetWorld()) return;

    for (int32 i = 0; i < GameData.PlayersCount - 1; ++i)
    {
        FActorSpawnParameters Parameters;
        Parameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        const auto Controller = GetWorld()->SpawnActor<AAIController>(AIControllerClass, Parameters);
        RestartPlayer(Controller);
    }
}
