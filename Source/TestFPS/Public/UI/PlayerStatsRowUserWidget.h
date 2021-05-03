// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "PlayerStatsRowUserWidget.generated.h"

class UImage;
class UTextBlock;

UCLASS()
class TESTFPS_API UPlayerStatsRowUserWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void SetPlayerNameText(const FText& Text);
    void SetKillsText(const FText& Text);
    void SetDeathsText(const FText& Text);
    void SetTeamText(const FText& Text);
    void SetPlayerIndicatorVisibility(bool Visible);
    
protected:
    UPROPERTY(meta = (BindWidget))
    UTextBlock* PlayerNameTextBlock;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* KillsTextBlock;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* DeathsTextBlock;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* TeamTextBlock;

    UPROPERTY(meta = (BindWidget))
    UImage* PlayerIndicatorImage;
};
