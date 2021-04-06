// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HealthComponent.h"
#include <Engine\World.h>
#include <TimerManager.h>

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

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
}

void UHealthComponent::OnHeal() 
{
    SetHealth(Health + HealthPerRate);

    if (Health >= MaxHealth)
    {
        GetWorld()->GetTimerManager().ClearTimer(AutoHealTimer);
    }
}

void UHealthComponent::SetHealth(float NewHealth)
{
    Health = FMath::Clamp(NewHealth, 0.f, MaxHealth);
    OnHealthChanged.Broadcast(NewHealth);
}
