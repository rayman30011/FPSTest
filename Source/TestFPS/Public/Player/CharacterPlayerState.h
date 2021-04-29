// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "CharacterPlayerState.generated.h"

UCLASS()
class TESTFPS_API ACharacterPlayerState : public APlayerState
{
    GENERATED_BODY()

public:
    int32 GetTeamID() const { return TeamID; }
    void SetTeamID(const int32 ID) { TeamID = ID; }

    FLinearColor GetTeamColor() const { return TeamColor; }
    void SetTeamColor(const FLinearColor& Color) { TeamColor = Color; }

    void AddKill() { ++KillsCount; }

    UFUNCTION(BlueprintCallable, Category = "Stats")
    int32 GetKillsCount() const { return KillsCount; }

    void AddDeath() { ++DeathCount; }
    int32 GetDeathCount() const { return DeathCount; }

    void LogInfo();
private:
    int32 TeamID;
    FLinearColor TeamColor;

    int32 KillsCount;
    int32 DeathCount;
};
