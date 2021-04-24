// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EQS/Tests/MyEnvQueryTest_PickupBeTaken.h"

#include "EnvironmentQuery/Items/EnvQueryItemType_ActorBase.h"
#include "Pickups/BasePickup.h"

UMyEnvQueryTest_PickupBeTaken::UMyEnvQueryTest_PickupBeTaken(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    Cost = EEnvTestCost::Low;
    ValidItemType = UEnvQueryItemType_ActorBase::StaticClass();
    SetWorkOnFloatValues(false);
}

void UMyEnvQueryTest_PickupBeTaken::RunTest(FEnvQueryInstance& QueryInstance) const
{
    const auto DataOwner = QueryInstance.Owner.Get();
    BoolValue.BindData(DataOwner, QueryInstance.QueryID);
    const bool WantsBeTaken = BoolValue.GetValue();
    
    for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
    {
        const auto ItemActor = GetItemActor(QueryInstance, It.GetIndex());
        const auto Pickup = Cast<ABasePickup>(ItemActor);
        if (!Pickup) continue;

        const auto CouldBeTaken = Pickup->BeTaken();
        It.SetScore(TestPurpose, FilterType, CouldBeTaken, WantsBeTaken);
    }
}
