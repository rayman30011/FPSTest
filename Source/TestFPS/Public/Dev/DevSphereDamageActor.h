// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DevSphereDamageActor.generated.h"

class USceneComponent;

UCLASS()
class TESTFPS_API ADevSphereDamageActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADevSphereDamageActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USceneComponent* SceneComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Radius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Damage = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FColor Color= FColor::Red;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool DoFullDamage = true;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
