// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/AmmoPackPickup.h"

#include <TestFPS/Public/Utils.h>

#include "HealthComponent.h"
#include "WeaponComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogAmmoPackPickup, All, All);

bool AAmmoPackPickup::GivePickupTo(APawn* Pawn)
{
    const auto HealthComponent = Utils::GetPlayerComponent<UHealthComponent>(Pawn);
    if (!HealthComponent || HealthComponent->IsDead()) return false;

    const auto WeaponComponent = Utils::GetPlayerComponent<UWeaponComponent>(Pawn);
    if (!WeaponComponent) return false;

    return WeaponComponent->TryToAddClips(WeaponClass, ClipsAmount);
}
