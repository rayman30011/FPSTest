// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "CoreTypes.h"
#include "Engine/GameInstance.h"
#include "ShooterGameInstance.generated.h"


UCLASS()
class TESTFPS_API UShooterGameInstance : public UGameInstance
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    FLevelData GetStartupLevel() const { return StartupLevel; }

    UFUNCTION(BlueprintCallable)
    void SetStartupLevel(const FLevelData& Data) { StartupLevel = Data; }

    UFUNCTION(BlueprintCallable)
    FName GetMenuLevelName() const { return MenuLevelName; }

    UFUNCTION(BlueprintCallable)
    TArray<FLevelData> GetLevelsData() const  { return LevelsData; }

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Game", meta = (ToolTip = "Level name must be unique"))
    TArray<FLevelData> LevelsData;

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    FName MenuLevelName = NAME_None;

private:
    FLevelData StartupLevel;
};
