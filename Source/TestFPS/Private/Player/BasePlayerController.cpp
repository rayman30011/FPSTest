// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BasePlayerController.h"
#include "RespawnComponent.h"

ABasePlayerController::ABasePlayerController()
{
    RespawnComponent = CreateDefaultSubobject<URespawnComponent>("RespawnComponent");
}

void ABasePlayerController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    OnNewPawn.Broadcast(InPawn);
}
