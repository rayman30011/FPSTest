// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameOverUserWidget.h"

#include "ShooterGameModeBase.h"
#include "Components/VerticalBox.h"
#include "Player/CharacterPlayerState.h"
#include "UI/PlayerStatsRowUserWidget.h"

bool UGameOverUserWidget::Initialize()
{
    if (GetWorld())
    {
        const auto GameMode = Cast<AShooterGameModeBase>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->OnMatchStateChanged.AddUObject(this, &UGameOverUserWidget::OnMatchStateChanged);
        } 
    }

    return  Super::Initialize();
}

void UGameOverUserWidget::OnMatchStateChanged(EMatchState State)
{
    if (State == EMatchState::GameOver)
    {
        UpdatePlayersStats();
    }
}

void UGameOverUserWidget::UpdatePlayersStats()
{
    if (!GetWorld() || !StatsBox) return;
    
    StatsBox->ClearChildren();

    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto Controller = It->Get();
        if (!Controller) continue;

        const auto PlayerState = Controller->GetPlayerState<ACharacterPlayerState>();
        if (!PlayerState) continue;

        const auto StatsRowWidget = CreateWidget<UPlayerStatsRowUserWidget>(GetWorld(), PlayerStatsRowWidgetClass);
        if (!StatsRowWidget) continue;

        StatsRowWidget->SetPlayerNameText(FText::FromString(PlayerState->GetPlayerName()));
        StatsRowWidget->SetKillsText(FText::FromString(FString::FromInt(PlayerState->GetKillsCount())));
        StatsRowWidget->SetTeamText(FText::FromString(FString::FromInt(PlayerState->GetTeamID())));
        StatsRowWidget->SetPlayerIndicatorVisibility(Controller->IsPlayerController());

        StatsBox->AddChild(StatsRowWidget);
    }
}
