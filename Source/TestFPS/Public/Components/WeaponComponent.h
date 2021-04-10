// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

class ABaseWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTFPS_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
    UWeaponComponent();

    void StartFire();
    void StopFire();
    void NextWeapon();

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TArray<TSubclassOf<ABaseWeapon>> WeaponClasses;

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

    void EquipWeapon(int32 Index);
    void SpawnWeapons();
    void AttachWeaponToSocket(ABaseWeapon* Weapon, USceneComponent* SceneComponent, const FName& SocketName);
    void PlayAnimMontage(UAnimMontage* Animation);
    void InitAnimations();
    void OnEquipFinished(USkeletalMeshComponent* MeshComp);
    bool CanFire() const;
    bool CanEquip() const;
};
