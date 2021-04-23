// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorators/AmmoEmptyDecorator.h"



#include "AIController.h"
#include "WeaponComponent.h"
#include "TestFPS/Public/Utils.h"

bool UAmmoEmptyDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    const auto Controller = OwnerComp.GetAIOwner();
    if (!Controller) return false;

    const auto WeaponComponent = Utils::GetPlayerComponent<UWeaponComponent>(Controller->GetPawn());
    if (!WeaponComponent) return false;

    const auto Weapon = WeaponComponent->GetWeaponByClass(WeaponClass);
    return Weapon && Weapon->IsEmptyAmmo();
}
