// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapon/BaseWeapon.h"

#include "WeaponComponent.generated.h"

class ABaseWeapon;

USTRUCT()
struct FWeaponData
{
    GENERATED_BODY()
    
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TSubclassOf<ABaseWeapon> WeaponClass;

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    UAnimMontage* ReloadAnimMontage;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTFPS_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
    UWeaponComponent();

    void StartFire();
    void StopFire();
    void NextWeapon();
    void Reload();

    bool GetWeaponUIData(FWeaponUIData& Data) const;
    bool GetCurrentWeaponAmmo(FAmmoData& AmmoData) const;

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TArray<FWeaponData> WeaponData;

    UPROPERTY()
    UAnimMontage* CurrentReloadAnimMontage = nullptr;
    
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName EquipSocketName;

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName ArmorySocketName;

    UPROPERTY(EditDefaultsOnly, Category = "Animations")
    UAnimMontage* EquipAnimMontage;

	virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
    UPROPERTY()
    ABaseWeapon* CurrentWeapon = nullptr;

    UPROPERTY()
    TArray<ABaseWeapon*> AvailableWeapons;

    int32 CurrentWeaponIndex = 0;
    bool EquipAnimInProgress = false;
    bool ReloadAnimInProgress = false;


    void OnEquipFinished(USkeletalMeshComponent* MeshComp);
    void OnReloadFinished(USkeletalMeshComponent* MeshComp);
    void OnWeaponSwitched(USkeletalMeshComponent* MeshComp);
    void OnClipEmpty();
    void ChangeClip();
    
    void EquipWeapon(int32 Index);
    void SpawnWeapons();
    void AttachWeaponToSocket(ABaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);
    void PlayAnimMontage(UAnimMontage* Animation);
    void InitAnimations();
    bool CanFire() const;
    bool CanEquip() const;
    bool CanReload() const;
};
