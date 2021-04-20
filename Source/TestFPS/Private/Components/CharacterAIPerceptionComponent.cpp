// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/CharacterAIPerceptionComponent.h"
#include "AIController.h"
#include "HealthComponent.h"
#include "Perception/AISense_Sight.h"
#include "TestFPS/Public/Utils.h"

AActor* UCharacterAIPerceptionComponent::GetClosesEnemy() const
{
    TArray<AActor*> PerceivedActors;
    GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PerceivedActors);
    if (PerceivedActors.Num() == 0) return nullptr;

    const auto Controller = Cast<AAIController>(GetOwner());
    if (!Controller) return nullptr;

    const auto Pawn = Controller->GetPawn();
    if (!Pawn) return nullptr;

    float BestDistance = MAX_FLT;
    AActor* BestPawn = nullptr;

    for (auto PerceivedActor : PerceivedActors)
    {
        const auto HealthComponent = Utils::GetPlayerComponent<UHealthComponent>(PerceivedActor);
        if (HealthComponent || !HealthComponent->IsDead())
        {
            const auto Distance = FVector::Distance(PerceivedActor->GetActorLocation(), Pawn->GetActorLocation());
            if (Distance < BestDistance)
            {
                BestDistance = Distance;
                BestPawn = PerceivedActor;
            }
        }
    }

    return BestPawn;
}
