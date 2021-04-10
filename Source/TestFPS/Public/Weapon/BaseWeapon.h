// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

class USkeletalMeshComponent;
class APlayerController;

USTRUCT(BlueprintType)
struct FAmmoData
{
    GENERATED_BODY()
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    int32 Bullets;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (EditContition = "!Infinite"))
    int32 Clips;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    bool Infinite;
};

UCLASS()
class TESTFPS_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseWeapon();

	virtual void StartFire();
	virtual void StopFire();

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

	virtual void BeginPlay() override;
	virtual void MakeShoot();
    virtual bool GetTraceData(FVector &Start, FVector &End) const;
    
    APlayerController* GetPlayerController() const;
    bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
    FVector GetMuzzleLocation() const;

    void DecreaseAmmo();
    bool IsEmptyAmmo() const;
    bool IsClipEmpty() const;
    void ChangeClip();
    void LogAmmo();
private:
    FAmmoData CurrentAmmo;
};
