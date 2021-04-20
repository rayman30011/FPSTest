// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/AIWeaponComponent.h"

void UAIWeaponComponent::StartFire()
{
    if (!CanFire()) return;

    if (CurrentWeapon->IsEmptyAmmo())
    {
        NextWeapon();
    }
    else
    {
        CurrentWeapon->StartFire();
    }
}

void UAIWeaponComponent::NextWeapon()
{
    if (!CanEquip()) return;
    int32 NextIndex = (CurrentWeaponIndex + 1) % AvailableWeapons.Num();
    while (NextIndex != CurrentWeaponIndex)
    {
        if (!AvailableWeapons[NextIndex]->IsEmptyAmmo()) break;;
        NextIndex = (NextIndex + 1) % AvailableWeapons.Num();
    }

    if (CurrentWeaponIndex != NextIndex)
    {
        CurrentWeaponIndex = NextIndex;
        EquipWeapon(CurrentWeaponIndex);
    }
}
