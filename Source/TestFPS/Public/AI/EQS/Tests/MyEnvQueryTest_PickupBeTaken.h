// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "MyEnvQueryTest_PickupBeTaken.generated.h"

/**
 * 
 */
UCLASS()
class TESTFPS_API UMyEnvQueryTest_PickupBeTaken : public UEnvQueryTest
{
    GENERATED_BODY()

public:
    UMyEnvQueryTest_PickupBeTaken(const FObjectInitializer& ObjectInitializer);

    virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;
};
