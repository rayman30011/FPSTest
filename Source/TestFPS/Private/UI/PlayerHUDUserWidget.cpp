// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerHUDUserWidget.h"

#include "HealthComponent.h"
#include "WeaponComponent.h"
#include "TestFPS/Public/Utils.h"

float UPlayerHUDUserWidget::GetHealthPercent() const
{
    const auto HealthComponent = Utils::GetPlayerComponent<UHealthComponent>(GetOwningPlayerPawn());
    if (!HealthComponent) return 0.f;

    return HealthComponent->GetHealthPercent();
}

bool UPlayerHUDUserWidget::GetWeaponUIData(FWeaponUIData& Data) const
{
    const auto WeaponComponent = Utils::GetPlayerComponent<UWeaponComponent>(GetOwningPlayerPawn());
    if (!WeaponComponent) return false;

    return WeaponComponent->GetWeaponUIData(Data);
}

bool UPlayerHUDUserWidget::GetWeaponData(FAmmoData& Data) const
{
    const auto WeaponComponent = Utils::GetPlayerComponent<UWeaponComponent>(GetOwningPlayerPawn());
    if (!WeaponComponent) return false;

    return WeaponComponent->GetCurrentWeaponAmmo(Data);
}

bool UPlayerHUDUserWidget::IsPlayerAlive() const
{
    const auto HealthComponent = Utils::GetPlayerComponent<UHealthComponent>(GetOwningPlayerPawn());
    return HealthComponent && !HealthComponent->IsDead();
}

bool UPlayerHUDUserWidget::IsPlayerSpectating() const
{
    const auto Controller = GetOwningPlayer();
    return Controller && Controller->GetStateName() == NAME_Spectating;
}

bool UPlayerHUDUserWidget::Initialize()
{
    const auto HealthComponent = Utils::GetPlayerComponent<UHealthComponent>(GetOwningPlayerPawn());
    if (HealthComponent)
    {
        HealthComponent->OnHealthChanged.AddUObject(this, &UPlayerHUDUserWidget::OnHealthChanged);
    }

    return Super::Initialize();
}

void UPlayerHUDUserWidget::OnHealthChanged(float Health, float Delta)
{
    if (Delta < 0)
    {
        OnTakeDamage();
    }
}
