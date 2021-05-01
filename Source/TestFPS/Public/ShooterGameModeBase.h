// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "CoreTypes.h"
#include "GameFramework/GameModeBase.h"
#include "Player/PlayerCharacter.h"

#include "ShooterGameModeBase.generated.h"

class AAIController;

UCLASS()
class TESTFPS_API AShooterGameModeBase : public AGameModeBase
{
    GENERATED_BODY()
public:
    AShooterGameModeBase();

    FOnMatchStateChangedSignature OnMatchStateChanged;

    virtual void StartPlay() override;
    virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

    void Killed(AController* Killer, AController* Victim);

    UFUNCTION(BlueprintCallable, Category = "Game")
    int32 GetRoundCountDown() const { return RoundCountDown; }

    UFUNCTION(BlueprintCallable, Category = "Game")
    int32 GetCurrentRound() const { return CurrentRound; }

    void RespawnRequest(AController* Controller);

    virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate) override;
    virtual bool ClearPause() override;

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Game")
    TSubclassOf<AAIController> AIControllerClass;

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    TSubclassOf<APawn> CharacterClass;

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    FGameData GameData;

private:
    EMatchState MatchState = EMatchState::WaitingToStart;
    int32 CurrentRound;
    int32 RoundCountDown;
    FTimerHandle GameRoundTimerHandle;

    void SpawnBots();
    void StartRound();
    void GameTimerUpdate();

    void ResetPlayers();
    void ResetOnePlayer(AController* Controller);

    void CreateTeamsInfo();
    FLinearColor GetColorByTeamID(int32 ID);
    void SetPlayerColor(const AController* Controller);

    void LogPlayerInfo();

    void StartRespawn(AController* Controller);

    void GameOver();

    void SetMatchState(EMatchState NewState);
};
