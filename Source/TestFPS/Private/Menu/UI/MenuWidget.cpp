// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/UI/MenuWidget.h"


#include "ShooterGameInstance.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Kismet/GameplayStatics.h"
#include "Menu/UI/LevelItemWidget.h"

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

    InitLevelItems();
}

void UMenuWidget::OnStartGame()
{
    const auto GameInstance = GetGameInstance();
    if (!GameInstance) return;

    UGameplayStatics::OpenLevel(this, GameInstance->GetStartupLevel().LevelName);
}

void UMenuWidget::OnExitGame()
{
    UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}

void UMenuWidget::InitLevelItems()
{
    const auto GameInstance = GetGameInstance();
    if (!GameInstance) return;

    checkf(GameInstance->GetLevelsData().Num() != 0, TEXT("LevelsData is empty"));

    if (!LevelsBox) return;
    LevelsBox->ClearChildren();

    for (auto LevelData : GameInstance->GetLevelsData())
    {
        const auto LevelItemWidget = CreateWidget<ULevelItemWidget>(GetWorld(), LevelItemWidgetClass);
        if (!LevelItemWidget) continue;

        LevelItemWidget->SetLevelData(LevelData);
        LevelItemWidget->OnLevelSelected.AddUObject(this, &UMenuWidget::OnLevelSelected);

        LevelsBox->AddChild(LevelItemWidget);
        LevelItemWidgets.Add(LevelItemWidget);
    }
}

void UMenuWidget::OnLevelSelected(const FLevelData& Data)
{
    const auto GameInstance = GetGameInstance();
    if (!GameInstance) return;

    GameInstance->SetStartupLevel(Data);
}

UShooterGameInstance* UMenuWidget::GetGameInstance() const
{
    if (!GetWorld()) return nullptr;
    return GetWorld()->GetGameInstance<UShooterGameInstance>();
}
