// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/UI/MenuWidget.h"


#include "ShooterGameInstance.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogMenu, All, All);

void UMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (StartButton)
    {
        StartButton->OnClicked.AddDynamic(this, &UMenuWidget::OnStartGame);
    }

    if (ExitButton)
    {
        ExitButton->OnClicked.AddDynamic(this, &UMenuWidget::OnExitGame);
    }
}

void UMenuWidget::OnStartGame()
{
    if (!GetWorld()) return;

    const auto GameInstance = GetWorld()->GetGameInstance<UShooterGameInstance>();
    if (!GameInstance) return;

    if (GameInstance->GetStartupLevelName().IsNone())
    {
        UE_LOG(LogMenu, Warning, TEXT("Level name is NONE"));
        return;
    }

    UGameplayStatics::OpenLevel(this, GameInstance->GetStartupLevelName());
}

void UMenuWidget::OnExitGame()
{
    UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}
