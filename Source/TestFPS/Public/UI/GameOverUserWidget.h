// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TestFPS/Public/CoreTypes.h"


#include "GameOverUserWidget.generated.h"


class UVerticalBox;
UCLASS()
class TESTFPS_API UGameOverUserWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    virtual bool Initialize() override;

protected:
    UPROPERTY(meta = (BindWidget))
    UVerticalBox* StatsBox;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PlayerStatsRowWidgetClass;

private:
    void OnMatchStateChanged(EMatchState State);
    void UpdatePlayersStats();
};
