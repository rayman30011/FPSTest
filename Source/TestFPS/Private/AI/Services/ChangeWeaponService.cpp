// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/ChangeWeaponService.h"



#include "AIController.h"
#include "AIWeaponComponent.h"
#include "TestFPS/Public/Utils.h"

UChangeWeaponService::UChangeWeaponService()
{
    NodeName = "ChangeWeapon";
}

void UChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    const auto Controller = OwnerComp.GetAIOwner();
    const auto WeaponComponent = Utils::GetPlayerComponent<UAIWeaponComponent>(Controller->GetPawn());
    if (WeaponComponent && FMath::FRand() <= Priority)
    {
        WeaponComponent->NextWeapon();
    }
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
