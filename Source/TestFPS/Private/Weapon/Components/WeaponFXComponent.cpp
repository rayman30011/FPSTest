// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/Components/WeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DecalComponent.h"
#include "TestFPS/Public/CoreTypes.h"

// Sets default values for this component's properties
UWeaponFXComponent::UWeaponFXComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UWeaponFXComponent::PlayImpactFX(const FHitResult& Hit)
{
    auto ImpactData = DefaultImpactData;

    if (Hit.PhysMaterial.IsValid())
    {
        const auto PhysMat = Hit.PhysMaterial.Get();
        if (ImpactDataMap.Contains(PhysMat))
        {
            ImpactData = ImpactDataMap[PhysMat];
        }
    }

    UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ImpactData.NiagaraEffect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
    auto DecalComponent = UGameplayStatics::SpawnDecalAtLocation(
        GetWorld(), ImpactData.DecalData.Material, ImpactData.DecalData.Size,
        Hit.ImpactPoint, Hit.ImpactNormal.Rotation(), ImpactData.DecalData.LifeTime);

    if (DecalComponent)
    {
        DecalComponent->SetFadeOut(ImpactData.DecalData.LifeTime, ImpactData.DecalData.FadeOutTime);
    }
}
