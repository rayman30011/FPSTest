// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorators/HealthPercentDecorator.h"



#include "AIController.h"
#include "HealthComponent.h"
#include "TestFPS/Public/Utils.h"

bool UHealthPercentDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    const auto Controller = OwnerComp.GetAIOwner();
    if (!Controller) return false;

    const auto HealthComponent = Utils::GetPlayerComponent<UHealthComponent>(Controller->GetPawn());
    if (!HealthComponent || HealthComponent->IsDead()) return false;

    return HealthComponent->GetHealthPercent() <= HealthPercent;
}
