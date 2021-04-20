// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/CharacterAIController.h"


#include "CharacterAIPerceptionComponent.h"
#include "AI/AIPlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

ACharacterAIController::ACharacterAIController()
{
    CustomPerceptionComponent = CreateDefaultSubobject<UCharacterAIPerceptionComponent>("CustomPerceptionComponent");
    SetPerceptionComponent(*CustomPerceptionComponent);
}

void ACharacterAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    const auto AICharacter = Cast<AAIPlayerCharacter>(InPawn);
    if (AICharacter)
    {
        RunBehaviorTree(AICharacter->BehaviorTree);
    }
}

void ACharacterAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    const auto AimActor = GetFocusOnActor();
    SetFocus(AimActor);
}

AActor* ACharacterAIController::GetFocusOnActor() const
{
    if (!GetBlackboardComponent()) return nullptr;
    return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}
