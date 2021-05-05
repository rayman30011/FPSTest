// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ShooterGameInstance.generated.h"


UCLASS()
class TESTFPS_API UShooterGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    FName GetStartupLevelName() const { return StartupLevelName; }
    
    UFUNCTION(BlueprintCallable)
    FName GetMenuLevelName() const { return MenuLevelName; }
    
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Game")
    FName StartupLevelName = NAME_None;

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    FName MenuLevelName = NAME_None;
};
