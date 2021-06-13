// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TestFPS/Public/CoreTypes.h"
#include "UI/BaseWidget.h"



#include "MenuWidget.generated.h"

class UButton;
class UHorizontalBox;
class UShooterGameInstance;
class ULevelItemWidget;

UCLASS()
class TESTFPS_API UMenuWidget : public UBaseWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    UButton* StartButton;

    UPROPERTY(meta = (BindWidget))
    UButton* ExitButton;
    
    UPROPERTY(meta = (BindWidget))
    UHorizontalBox* LevelsBox;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> LevelItemWidgetClass;

    virtual void NativeOnInitialized() override;

private:
    UPROPERTY()
    TArray<ULevelItemWidget*> LevelItemWidgets; 
    
    UFUNCTION()
    void OnStartGame();
    
    UFUNCTION()
    void OnExitGame();

    void InitLevelItems();
    void OnLevelSelected(const FLevelData& Data);

    UShooterGameInstance* GetGameInstance() const;
};
