// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HealthComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

    check(MaxHealth > 0);
    
	Health = MaxHealth;
    SetHealth(Health);

	AActor* Owner = GetOwner();
    if (Owner)
    {
        Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnTakeDamage);
    }
}

void UHealthComponent::OnTakeDamage(
    AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
    if (Damage < 0.f || IsDead()) return;

    SetHealth(Health - Damage);

    if (GetWorld()->GetTimerManager().IsTimerActive(AutoHealTimer))
    {
        GetWorld()->GetTimerManager().ClearTimer(AutoHealTimer);
    }

    if (IsDead())
    {
        OnDeath.Broadcast();
    }
    else if (EnableAutoHeal)
    {
        GetWorld()->GetTimerManager().SetTimer(AutoHealTimer, this, &UHealthComponent::OnHeal, AutoHealUpdateRate, true, AutoHealDelay);
    }

    PlayShake();
}

void UHealthComponent::OnHeal() 
{
    SetHealth(Health + HealthPerRate);

    if (Health >= MaxHealth)
    {
        GetWorld()->GetTimerManager().ClearTimer(AutoHealTimer);
    }
}

void UHealthComponent::PlayShake()
{
    if (IsDead()) return;

    const auto Player = Cast<APawn>(GetOwner());
    if (!Player) return;

    const auto Controller = Player->GetController<APlayerController>();
    if (!Controller || !Controller->PlayerCameraManager) return;

    Controller->PlayerCameraManager->StartCameraShake(CameraShakeClass);
}

void UHealthComponent::SetHealth(float NewHealth)
{
    const auto NextHealth = FMath::Clamp(NewHealth, 0.f, MaxHealth);
    const auto HealthDelta = NewHealth - Health;
    Health = NextHealth;
    OnHealthChanged.Broadcast(Health, HealthDelta);
}

bool UHealthComponent::TryAddHealth(float AmountHealth)
{
    if (FMath::IsNearlyEqual(Health, MaxHealth) || IsDead()) return false;
    SetHealth(AmountHealth + Health);
    return true;
}
