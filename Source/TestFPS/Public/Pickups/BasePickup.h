// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "BasePickup.generated.h"

class USphereComponent;

UCLASS()
class TESTFPS_API ABasePickup : public AActor
{
    GENERATED_BODY()

public:
    ABasePickup();

protected:
    UPROPERTY(VisibleAnywhere, Category = "Pickup")
    USphereComponent* CollisionComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Pickup")
    float RespawnTime = 3.f;


    virtual void BeginPlay() override;
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

    virtual bool GivePickupTo(APawn* Pawn);

public:
    virtual void Tick(float DeltaTime) override;

private:
    void PickupWasTaken();
    void Respawn();
};
