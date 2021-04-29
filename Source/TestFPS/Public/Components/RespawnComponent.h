// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RespawnComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTFPS_API URespawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	URespawnComponent();

    void Respawn(int32 RespawnTime);

    UFUNCTION(BlueprintCallable, Category = "Respawn")
    int32 GetRespawnCountDown() const { return RespawnCountDown; }

    UFUNCTION(BlueprintCallable, Category = "Respawn")
    bool IsRespawnInProgress() const;

private:
    FTimerHandle RespawnTimerHandle;
    int32 RespawnCountDown = 0;

    void RespawnTimerUpdate();
};
