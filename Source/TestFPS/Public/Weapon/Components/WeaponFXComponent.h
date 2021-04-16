// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponFXComponent.generated.h"

class UNiagaraSystem;
class UPhysicalMaterial;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TESTFPS_API UWeaponFXComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UWeaponFXComponent();

    void PlayImpactFX(const FHitResult& Hit);

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FX")
    UNiagaraSystem* DefaultEffect;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "FX")
    TMap<UPhysicalMaterial*, UNiagaraSystem*> EffectsMap;
};
