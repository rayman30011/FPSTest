// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

class USkeletalMeshComponent;
class APlayerController;

UCLASS()
class TESTFPS_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseWeapon();

	virtual void Fire();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    FName MuzzleSocketName = "MuzzleFlash";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float TranceLenth = 1500;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float Damage = 20;

	virtual void BeginPlay() override;

	void MakeShoot();

private:	
	APlayerController* GetPlayerController() const;
    bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
};
