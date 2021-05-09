// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/UI/LevelItemWidget.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void ULevelItemWidget::SetLevelData(const FLevelData& Data)
{
    LevelData = Data;
    if (LevelNameText)
    {
        LevelNameText->SetText(FText::FromName(LevelData.LevelDisplayName));
    }

    if (LevelImage)
    {
        LevelImage->SetBrushFromTexture(LevelData.LevelIcon);
    }
}

void ULevelItemWidget::NativeOnInitialized()
{
    if (LevelSelectButton)
    {
        LevelSelectButton->OnClicked.AddDynamic(this, &ULevelItemWidget::OnLevelSelectButtonClicked);
    }
}

void ULevelItemWidget::OnLevelSelectButtonClicked()
{
    OnLevelSelected.Broadcast(LevelData);
}
