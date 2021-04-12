// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/BasePickup.h"

DEFINE_LOG_CATEGORY_STATIC(LogBasePickup, All, All);

#include "Components/SphereComponent.h"

ABasePickup::ABasePickup()
{
    PrimaryActorTick.bCanEverTick = true;
    CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    CollisionComponent->InitSphereRadius(50.f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
    SetRootComponent(CollisionComponent);
}

void ABasePickup::BeginPlay()
{
    Super::BeginPlay();
}

void ABasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    UE_LOG(LogBasePickup, Display, TEXT("Overlap %s"), *OtherActor->GetName());
    Destroy();
}

void ABasePickup::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
