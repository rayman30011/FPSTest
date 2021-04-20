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

    virtual void StartFire();
    void StopFire();
    virtual void NextWeapon();
    void Reload();

    bool GetWeaponUIData(FWeaponUIData& Data) const;
    bool GetCurrentWeaponAmmo(FAmmoData& AmmoData) const;
    bool TryToAddClips(const TSubclassOf<ABaseWeapon> Class, int32 ClipsAmount);

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
    
    UPROPERTY()
    ABaseWeapon* CurrentWeapon = nullptr;

    UPROPERTY()
    TArray<ABaseWeapon*> AvailableWeapons;

	virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    bool CanFire() const;
    bool CanEquip() const;
    void EquipWeapon(int32 Index);
    
    int32 CurrentWeaponIndex = 0;
private:
    bool EquipAnimInProgress = false;
    bool ReloadAnimInProgress = false;

    void OnEquipFinished(USkeletalMeshComponent* MeshComp);
    void OnReloadFinished(USkeletalMeshComponent* MeshComp);
    void OnWeaponSwitched(USkeletalMeshComponent* MeshComp);
    void OnClipEmpty(ABaseWeapon* Weapon);
    void ChangeClip();
    
    void SpawnWeapons();
    void AttachWeaponToSocket(ABaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);
    void PlayAnimMontage(UAnimMontage* Animation);
    void InitAnimations();
    bool CanReload() const;
};
