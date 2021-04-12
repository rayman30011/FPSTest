// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/WeaponComponent.h"
#include "Weapon/BaseWeapon.h"
#include "GameFramework/Character.h"
#include "Animations/EquipRifleAnimNotify.h"
#include "Animations/ReloadFinishedAnimNotify.h"
#include "Animations/Notify/WeaponSwitchedAnimNotify.h"
#include "Weapon/AnimUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All);

UWeaponComponent::UWeaponComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UWeaponComponent::BeginPlay()
{
    Super::BeginPlay();

    CurrentWeaponIndex = 0;
    InitAnimations();
    SpawnWeapons();
    EquipWeapon(CurrentWeaponIndex);
}

void UWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    CurrentWeapon = nullptr;
    for (auto Weapon : AvailableWeapons)
    {
        Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
        Weapon->Destroy();
    }

    AvailableWeapons.Empty();
    Super::EndPlay(EndPlayReason);
}

void UWeaponComponent::EquipWeapon(int32 Index)
{
    if (Index < 0 || Index >= WeaponData.Num())
    {
        UE_LOG(LogWeaponComponent, Warning, TEXT("Invalid wepon index"))
        return;
    }

    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character) return;
    
    EquipAnimInProgress = true;
    PlayAnimMontage(EquipAnimMontage);
}

void UWeaponComponent::SpawnWeapons()
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character || !GetWorld()) return;

    for (auto Data : WeaponData)
    {
        auto Weapon = GetWorld()->SpawnActor<ABaseWeapon>(Data.WeaponClass);        
        if (!Weapon) continue;

        Weapon->OnClipEmpty.AddUObject(this, &UWeaponComponent::OnClipEmpty);
        Weapon->SetOwner(GetOwner());
        AvailableWeapons.Add(Weapon);

        AttachWeaponToSocket(Weapon, Character->GetMesh(), ArmorySocketName);
    }
}

void UWeaponComponent::AttachWeaponToSocket(ABaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName)
{
    if (!Weapon || !SceneComponent) return;

    const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
    Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}

void UWeaponComponent::StartFire()
{
    if (!CanFire()) return;
    CurrentWeapon->StartFire();
}

void UWeaponComponent::StopFire()
{
    if (!CurrentWeapon) return;
    CurrentWeapon->StopFire();
}

void UWeaponComponent::NextWeapon()
{
    if (!CanEquip()) return;

    CurrentWeaponIndex = (CurrentWeaponIndex + 1) % AvailableWeapons.Num();
    EquipWeapon(CurrentWeaponIndex);
}

void UWeaponComponent::Reload()
{
    ChangeClip();
}

bool UWeaponComponent::GetWeaponUIData(FWeaponUIData& Data) const
{
    if (CurrentWeapon)
    {
        Data = CurrentWeapon->GetUIData();
        return true;
    }

    return false;
}

void UWeaponComponent::PlayAnimMontage(UAnimMontage* Animation)
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character || !GetWorld()) return;

    Character->PlayAnimMontage(Animation);
}

void UWeaponComponent::InitAnimations()
{
    if (!EquipAnimMontage) return;

    auto EquipFinishNotify = AnimUtils::FindNotifyByClass<UEquipRifleAnimNotify>(EquipAnimMontage);
    if (EquipFinishNotify)
    {
        EquipFinishNotify->OnNotified.AddUObject(this, &UWeaponComponent::OnEquipFinished);
    }
    else
    {
        UE_LOG(LogWeaponComponent, Error, TEXT("EquipFinishNotify not found"));
        checkNoEntry();
    }

    auto WeaponSwitchedNotify = AnimUtils::FindNotifyByClass<UWeaponSwitchedAnimNotify>(EquipAnimMontage);
    if (WeaponSwitchedNotify)
    {
        WeaponSwitchedNotify->OnNotified.AddUObject(this, &UWeaponComponent::OnWeaponSwitched);
    }
    else
    {
        UE_LOG(LogWeaponComponent, Error, TEXT("EquipFinishNotify not found"));
        checkNoEntry();
    }

    for (auto Data : WeaponData)
    {
        auto ReloadFinishNotify = AnimUtils::FindNotifyByClass<UReloadFinishedAnimNotify>(Data.ReloadAnimMontage);
        if (!ReloadFinishNotify)
        {
            UE_LOG(LogWeaponComponent, Error, TEXT("ReloadFinishNotify not found"));
            checkNoEntry();
        }
        
        ReloadFinishNotify->OnNotified.AddUObject(this, &UWeaponComponent::OnReloadFinished);
    }
    
}

void UWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComp)
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character || Character->GetMesh() != MeshComp) return;

    EquipAnimInProgress = false;
}

void UWeaponComponent::OnReloadFinished(USkeletalMeshComponent* MeshComp)
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character || Character->GetMesh() != MeshComp) return;

    ReloadAnimInProgress = false;
    
}

void UWeaponComponent::OnWeaponSwitched(USkeletalMeshComponent* MeshComp)
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character) return;
    
    if (CurrentWeapon)
    {
        CurrentWeapon->StopFire();
        AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), ArmorySocketName);
    }

    CurrentWeapon = AvailableWeapons[CurrentWeaponIndex];
    const auto CurrentWeaponData = WeaponData.FindByPredicate([&](const FWeaponData& Data)
    {
        return Data.WeaponClass == CurrentWeapon->GetClass();
    });

    CurrentReloadAnimMontage = CurrentWeaponData ? CurrentWeaponData->ReloadAnimMontage : nullptr;
    AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), EquipSocketName);
}

void UWeaponComponent::OnClipEmpty()
{
    ChangeClip();
}

void UWeaponComponent::ChangeClip()
{
    if (!CanReload()) return;
    
    CurrentWeapon->StopFire();
    CurrentWeapon->ChangeClip();
    ReloadAnimInProgress = true;
    PlayAnimMontage(CurrentReloadAnimMontage);
}

bool UWeaponComponent::CanFire() const
{
    return CurrentWeapon && !EquipAnimInProgress && !ReloadAnimInProgress;
}

bool UWeaponComponent::CanEquip() const
{
    return !EquipAnimInProgress;
}

bool UWeaponComponent::CanReload() const
{
    return CurrentWeapon && !EquipAnimInProgress && !ReloadAnimInProgress && CurrentWeapon->CanReload();
}
