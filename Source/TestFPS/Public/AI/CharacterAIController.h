// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CharacterAIController.generated.h"

class UCharacterAIPerceptionComponent;

UCLASS()
class TESTFPS_API ACharacterAIController : public AAIController
{
    GENERATED_BODY()

public:
    ACharacterAIController();
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCharacterAIPerceptionComponent* CustomPerceptionComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
    FName FocusOnKeyName = "EnemyActor";

    virtual void OnPossess(APawn* InPawn) override;
    virtual void Tick(float DeltaSeconds) override;

private:
    AActor* GetFocusOnActor() const;
};
