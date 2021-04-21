// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/FireService.h"



#include "AIController.h"
#include "WeaponComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "TestFPS/Public/Utils.h"

UFireService::UFireService()
{
    NodeName = "Fire";
}

void UFireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    const auto Blackboard = OwnerComp.GetBlackboardComponent();
    const auto Controller = OwnerComp.GetAIOwner();

    const bool HasAim = Blackboard && Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);
    if (Controller)
    {
        const auto WeaponComponent = Utils::GetPlayerComponent<UWeaponComponent>(Controller->GetPawn());
        if (WeaponComponent)
        {
            HasAim ? WeaponComponent->StartFire() : WeaponComponent->StopFire();
        }
    }
    
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
