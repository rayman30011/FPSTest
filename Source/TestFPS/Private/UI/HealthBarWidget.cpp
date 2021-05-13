// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HealthBarWidget.h"

#include "Components/ProgressBar.h"

void UHealthBarWidget::SetHealthPercent(float Percent)
{
    if (!HealthProgressBar) return;

    const auto HealthBarVisibility = (Percent > PercentVisibilityThreshold || FMath::IsNearlyZero(Percent))
        ? ESlateVisibility::Hidden : ESlateVisibility::Visible;

    HealthProgressBar->SetVisibility(HealthBarVisibility);
    HealthProgressBar->SetPercent(Percent);

    const auto HeathBarColor = Percent > PercentColorThreshold ? GoodColor : BadColor;
    HealthProgressBar->SetFillColorAndOpacity(HeathBarColor);
}
