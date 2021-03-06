// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TestFPS/Public/CoreTypes.h"

#include "BasePlayerController.generated.h"

class URespawnComponent;

UCLASS()
class TESTFPS_API ABasePlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    ABasePlayerController();

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    URespawnComponent* RespawnComponent;

    virtual void BeginPlay() override;
    virtual void OnPossess(APawn* InPawn) override;
    virtual void SetupInputComponent() override;

private:
    void OnPauseGame();
    void OnMatchStateChanged(EMatchState State);
};
