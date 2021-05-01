// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PauseWidget.h"

#include "GameFramework/GameModeBase.h"

bool UPauseWidget::Initialize()
{
    const auto InitStatus = Super::Initialize();
    if (ClearPauseButton)
    {
        ClearPauseButton->OnClicked.AddDynamic(this, &UPauseWidget::OnClearPause);
    }

    return InitStatus;
}

void UPauseWidget::OnClearPause()
{
    if (!GetWorld() && !GetWorld()->GetAuthGameMode()) return;

    GetWorld()->GetAuthGameMode()->ClearPause();
}
