// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerStatsRowUserWidget.h"


#include "Components/Image.h"
#include "Components/TextBlock.h"

void UPlayerStatsRowUserWidget::SetPlayerNameText(const FText& Text)
{
    if (!PlayerNameTextBlock) return;
    PlayerNameTextBlock->SetText(Text);
}

void UPlayerStatsRowUserWidget::SetKillsText(const FText& Text)
{
    if (!KillsTextBlock) return;
    KillsTextBlock->SetText(Text);
}

void UPlayerStatsRowUserWidget::SetDeathsText(const FText& Text)
{
    if (!DeathsTextBlock) return;
    DeathsTextBlock->SetText(Text);
}

void UPlayerStatsRowUserWidget::SetTeamText(const FText& Text)
{
    if (!TeamTextBlock) return;
    TeamTextBlock->SetText(Text);
}

void UPlayerStatsRowUserWidget::SetPlayerIndicatorVisibility(bool Visible)
{
    if (!PlayerIndicatorImage) return;
    PlayerIndicatorImage->SetVisibility(Visible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}
