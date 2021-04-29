// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterGameModeBase.h"


#include "AIController.h"
#include "RespawnComponent.h"
#include "Player/CharacterPlayerState.h"
#include "Player/PlayerCharacter.h"
#include "TestFPS/Public/Utils.h"
#include "UI/GameHUD.h"

DEFINE_LOG_CATEGORY_STATIC(LogShooterGameMode, All, All);

AShooterGameModeBase::AShooterGameModeBase()
{
    DefaultPawnClass = APlayerCharacter::StaticClass();
    PlayerControllerClass = APlayerController::StaticClass();
    HUDClass = AGameHUD::StaticClass();
    PlayerStateClass = ACharacterPlayerState::StaticClass();
}

void AShooterGameModeBase::StartPlay()
{
    Super::StartPlay();

    SpawnBots();
    CreateTeamsInfo();
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

void AShooterGameModeBase::Killed(AController* Killer, AController* Victim)
{
    const auto KillerState = Killer ? Killer->GetPlayerState<ACharacterPlayerState>() : nullptr;
    const auto VictimState = Victim ? Victim->GetPlayerState<ACharacterPlayerState>() : nullptr;

    if (KillerState)
    {
        KillerState->AddKill();
    }

    if (VictimState)
    {
        VictimState->AddDeath();
    }

    StartRespawn(Victim);
    LogPlayerInfo();
}

void AShooterGameModeBase::RespawnRequest(AController* Controller)
{
    ResetOnePlayer(Controller);
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
    SetPlayerColor(Controller);
}

void AShooterGameModeBase::CreateTeamsInfo()
{
    if (!GetWorld()) return;

    int32 TeamID = 1;
    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto Controller = It->Get();
        if (!Controller) continue;

        const auto PlayerState = Cast<ACharacterPlayerState>(Controller->PlayerState);
        if (!PlayerState) continue;

        PlayerState->SetTeamID(TeamID);
        PlayerState->SetTeamColor(GetColorByTeamID(TeamID));
        SetPlayerColor(Controller);
        TeamID = TeamID == 1 ? 2 : 1;
    }
}

FLinearColor AShooterGameModeBase::GetColorByTeamID(int32 ID)
{
    if (ID - 1 < GameData.TeamColors.Num())
    {
        return GameData.TeamColors[ID - 1];
    }

    UE_LOG(LogShooterGameMode, Warning, TEXT("No color for TeamID %i"), ID);
    return GameData.DefaultColor;
}

void AShooterGameModeBase::SetPlayerColor(const AController* Controller)
{
    if (!Controller) return;
    
    const auto Character = Cast<APlayerCharacter>(Controller->GetPawn());
    if (!Character) return;

    const auto PlayerState = Cast<ACharacterPlayerState>(Controller->PlayerState);
    if (!PlayerState) return;

    Character->SetPlayerColor(PlayerState->GetTeamColor());
}

void AShooterGameModeBase::LogPlayerInfo()
{
    if (!GetWorld()) return;

    int32 TeamID = 1;
    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto Controller = It->Get();
        if (!Controller) continue;

        const auto PlayerState = Controller->GetPlayerState<ACharacterPlayerState>();
        if (!PlayerState) continue;

        PlayerState->LogInfo();
    }
}

void AShooterGameModeBase::StartRespawn(AController* Controller)
{
    const auto RespawnComponent = Utils::GetPlayerComponent<URespawnComponent>(Controller);
    if (!RespawnComponent) return;

    RespawnComponent->Respawn(GameData.RespawnTime);
}
