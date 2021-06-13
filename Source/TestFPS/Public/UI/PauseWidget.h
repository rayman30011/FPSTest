// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "BaseWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"

#include "PauseWidget.generated.h"


UCLASS()
class TESTFPS_API UPauseWidget : public UBaseWidget
{
    GENERATED_BODY()

protected:
    virtual void NativeOnInitialized() override;
    
    UPROPERTY(meta = (BindWidget))
    UButton* ClearPauseButton;

private:
    UFUNCTION()
    void OnClearPause();
};
