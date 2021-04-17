// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, float);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TESTFPS_API UHealthComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UHealthComponent();

    UFUNCTION(BlueprintCallable, Category = "Health")
    float IsDead() const { return Health <= 0.f; }

    UFUNCTION(BlueprintCallable, Category = "Health")
    float GetHealthPercent() const { return Health / MaxHealth; }

protected:
    virtual void BeginPlay() override;

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "0"))
    float MaxHealth = 100.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Auto Heal")
    bool EnableAutoHeal = true;

    UPROPERTY(EditAnywhere, Category = "Auto Heal", meta = (EditCondition = "EnableAutoHeal"))
    float AutoHealDelay = 3.f;

    UPROPERTY(EditAnywhere, Category = "Auto Heal", meta = (EditCondition = "EnableAutoHeal"))
    float AutoHealUpdateRate = 0.5f;

    UPROPERTY(EditAnywhere, Category = "Auto Heal", meta = (EditCondition = "EnableAutoHeal"))
    float HealthPerRate = 5.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
    TSubclassOf<UCameraShakeBase> CameraShakeClass;

    float GetHealth() const { return Health; }

    UFUNCTION(BlueprintCallable)
    void SetHealth(float NewHealth);

    bool TryAddHealth(float Amount);

    FOnDeath OnDeath;
    FOnHealthChanged OnHealthChanged;

private:
    float Health = 0.f;
    FTimerHandle AutoHealTimer;

    UFUNCTION()
    void OnTakeDamage(
        AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

    UFUNCTION()
    void OnHeal();

    void PlayShake();
};
