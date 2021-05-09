// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TestFPS/Public/CoreTypes.h"

#include "LevelItemWidget.generated.h"


class UButton;
class UTextBlock;
class UImage;

UCLASS()
class TESTFPS_API ULevelItemWidget : public UUserWidget
{
    GENERATED_BODY()
    
public:
    FOnLevelSelectedSignature OnLevelSelected;

    void SetLevelData(const FLevelData& Data);
    FLevelData GetLevelData() const { return LevelData; }
    
protected:
    UPROPERTY(meta = (BindWidget))
    UButton* LevelSelectButton;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* LevelNameText;

    UPROPERTY(meta = (BindWidget))
    UImage* LevelImage = nullptr;

    virtual void NativeOnInitialized() override;

private:
    FLevelData LevelData;

    UFUNCTION()
    void OnLevelSelectButtonClicked();
};
