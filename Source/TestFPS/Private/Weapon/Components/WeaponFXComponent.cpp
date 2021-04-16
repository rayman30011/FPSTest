// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Components/WeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values for this component's properties
UWeaponFXComponent::UWeaponFXComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UWeaponFXComponent::PlayImpactFX(const FHitResult& Hit)
{
    auto Effect = DefaultEffect;

    if (Hit.PhysMaterial.IsValid())
    {
        const auto PhysMat = Hit.PhysMaterial.Get();
        if (EffectsMap.Contains(PhysMat))
        {
            Effect = EffectsMap[PhysMat];
        }
    }
    
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Effect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());   
}

