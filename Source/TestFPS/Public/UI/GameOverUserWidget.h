// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TestFPS/Public/CoreTypes.h"


#include "GameOverUserWidget.generated.h"

class UButton;
class UVerticalBox;

UCLASS()
class TESTFPS_API UGameOverUserWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    UVerticalBox* StatsBox;

    UPROPERTY(meta = (BindWidget))
    UButton* ResetLevelButton;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PlayerStatsRowWidgetClass;

    virtual void NativeOnInitialized() override;

private:
    void OnMatchStateChanged(EMatchState State);
    void UpdatePlayersStats();

    UFUNCTION()
    void OnResetLevel();
};
