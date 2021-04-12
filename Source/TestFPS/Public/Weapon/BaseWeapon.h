// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestFPS/Public/CoreTypes.h"

#include "BaseWeapon.generated.h"

class USkeletalMeshComponent;
class APlayerController;

UCLASS()
class TESTFPS_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseWeapon();

    FOnClipEmptySignature OnClipEmpty;

	virtual void StartFire();
	virtual void StopFire();
    
    void ChangeClip();
    bool CanReload() const;

    FWeaponUIData GetUIData() const { return UIData; }
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    FName MuzzleSocketName = "MuzzleFlash";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float TranceLength = 1500;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float Damage = 20;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    FAmmoData DefaultAmmo = {15, 3, false};

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    FWeaponUIData UIData;
    
	virtual void BeginPlay() override;
	virtual void MakeShoot();
    virtual bool GetTraceData(FVector &Start, FVector &End) const;
    
    APlayerController* GetPlayerController() const;
    bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
    FVector GetMuzzleLocation() const;

    void DecreaseAmmo();
    bool IsEmptyAmmo() const;
    bool IsClipEmpty() const;
    void LogAmmo();
private:
    FAmmoData CurrentAmmo;
};
