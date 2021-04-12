// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerHUDUserWidget.h"

#include "HealthComponent.h"
#include "WeaponComponent.h"

float UPlayerHUDUserWidget::GetHealthPercent() const
{
    const auto Player = GetOwningPlayerPawn();
    if (!Player) return 0.f;

    const auto Component = Player->GetComponentByClass(UHealthComponent::StaticClass());
    const auto HealthComponent = Cast<UHealthComponent>(Component);
    if (!HealthComponent) return 0.f;

    return HealthComponent->GetHealthPercent();
}

bool UPlayerHUDUserWidget::GetWeaponUIData(FWeaponUIData& Data) const
{
    const auto Player = GetOwningPlayerPawn();
    if (!Player) return false;

    const auto Component = Player->GetComponentByClass(UWeaponComponent::StaticClass());
    const auto WeaponComponent = Cast<UWeaponComponent>(Component);
    if (!WeaponComponent) return false;

    return WeaponComponent->GetWeaponUIData(Data);
}
