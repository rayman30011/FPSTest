// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterGameModeBase.h"


#include "AIController.h"
#include "Player/PlayerCharacter.h"
#include "UI/GameHUD.h"

DEFINE_LOG_CATEGORY_STATIC(LogShooterGameMode, All, All);

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
    
    CurrentRound = 1;
    StartRound();
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

void AShooterGameModeBase::StartRound()
{
    RoundCountDown = GameData.RoundTime;
    GetWorldTimerManager().SetTimer(GameRoundTimerHandle, this, &AShooterGameModeBase::GameTimerUpdate, 1.0f, true);
}

void AShooterGameModeBase::GameTimerUpdate()
{
    UE_LOG(LogShooterGameMode, Display, TEXT("Time: %i / Round %i/%i"), RoundCountDown, CurrentRound, GameData.RoundsCount);
    if (--RoundCountDown == 0)
    {
        GetWorldTimerManager().ClearTimer(GameRoundTimerHandle);
        if (CurrentRound + 1 <= GameData.RoundsCount)
        {
            ++CurrentRound;
            ResetPlayers();
            StartRound();
        }
        else
        {
            UE_LOG(LogShooterGameMode, Warning, TEXT("Game Over"));
        }
    }
}

void AShooterGameModeBase::ResetPlayers()
{
    if (!GetWorld()) return;

    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        ResetOnePlayer(It->Get());
    }
}

void AShooterGameModeBase::ResetOnePlayer(AController* Controller)
{
    if (Controller && Controller->GetPawn())
    {
        Controller->GetPawn()->Reset();
    }
    RestartPlayer(Controller);
}
