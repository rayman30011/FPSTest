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

    virtual void StartPlay() override;
    virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;
protected:
    UPROPERTY(EditDefaultsOnly, Category = "Game")
    TSubclassOf<AAIController> AIControllerClass;

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    TSubclassOf<APawn> CharacterClass;

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    FGameData GameData;

private:
    int32 CurrentRound;
    int32 RoundCountDown;
    FTimerHandle GameRoundTimerHandle;

    void SpawnBots();
    void StartRound();
    void GameTimerUpdate();

    void ResetPlayers();
    void ResetOnePlayer(AController* Controller);
};
