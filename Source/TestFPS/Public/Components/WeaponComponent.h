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

    void Fire();

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TSubclassOf<ABaseWeapon> WeaponClass;

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName SocketName;

	virtual void BeginPlay() override;

private:
    void SpawnWeapon();

    UPROPERTY()
    ABaseWeapon* CurrentWeapon = nullptr;
};
