// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TestFPS/Public/CoreTypes.h"

#include "PlayerHUDUserWidget.generated.h"
/**
 * 
 */
UCLASS()
class TESTFPS_API UPlayerHUDUserWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "UI")
    float GetHealthPercent() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetWeaponUIData(FWeaponUIData& Data) const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetWeaponData(FAmmoData& Data) const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool IsPlayerAlive() const;
    
    UFUNCTION(BlueprintCallable, Category = "UI")
    bool IsPlayerSpectating() const;
};
