// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/UI/MenuWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (StartButton)
    {
        StartButton->OnClicked.AddDynamic(this, &UMenuWidget::OnStartGame);
    }
}

void UMenuWidget::OnStartGame()
{
    const FName LevelName = "M_Default";
    UGameplayStatics::OpenLevel(this, LevelName);
}
