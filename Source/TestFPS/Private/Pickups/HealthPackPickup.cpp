// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/HealthPackPickup.h"


#include "HealthComponent.h"
#include "TestFPS/Public/Utils.h"

bool AHealthPackPickup::GivePickupTo(APawn* Pawn)
{
    const auto HealthComponent = Utils::GetPlayerComponent<UHealthComponent>(Pawn);
    if (!HealthComponent) return false;
    
    return HealthComponent->TryAddHealth(HealthAmount);
}
