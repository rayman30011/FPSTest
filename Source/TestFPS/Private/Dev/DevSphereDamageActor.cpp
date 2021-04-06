// Fill out your copyright notice in the Description page of Project Settings.


#include "Dev/DevSphereDamageActor.h"
#include <DrawDebugHelpers.h>
#include <Kismet/GameplayStatics.h>

// Sets default values
ADevSphereDamageActor::ADevSphereDamageActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SpringArm");
    SceneComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ADevSphereDamageActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADevSphereDamageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 24, Color);
    UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), Radius, nullptr, {}, this, nullptr, DoFullDamage);
}

