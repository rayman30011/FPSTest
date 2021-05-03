// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameOverUserWidget.h"

#include "ShooterGameModeBase.h"
#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "Kismet/GameplayStatics.h"
#include "Player/CharacterPlayerState.h"
#include "UI/PlayerStatsRowUserWidget.h"

void UGameOverUserWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    
    if (GetWorld())
    {
        const auto GameMode = Cast<AShooterGameModeBase>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->OnMatchStateChanged.AddUObject(this, &UGameOverUserWidget::OnMatchStateChanged);
        } 
    }

    if (ResetLevelButton)
    {
        ResetLevelButton->OnClicked.AddDynamic(this, &UGameOverUserWidget::OnResetLevel);
    }
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

void UGameOverUserWidget::OnResetLevel()
{
    const FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this);
    UGameplayStatics::OpenLevel(this, FName(CurrentLevelName));
}
