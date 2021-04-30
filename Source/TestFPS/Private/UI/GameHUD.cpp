// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameHUD.h"
#include <Engine/Canvas.h>

#include "ShooterGameModeBase.h"
#include "Blueprint/UserWidget.h"

void AGameHUD::DrawHUD()
{
    Super::DrawHUD();
    //DrawCrossHair();
}

void AGameHUD::BeginPlay()
{
    Super::BeginPlay();

    check(GetWorld());
    
    const auto PlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass);
    if (PlayerHUDWidget)
    {
        PlayerHUDWidget->AddToViewport();
    }

    const auto GameMode = Cast<AShooterGameModeBase>(GetWorld()->GetAuthGameMode());
    if (GameMode)
    {
        GameMode->OnMatchStateChanged.AddUObject(this, &AGameHUD::OnMatchStateChanged);
    }
}

void AGameHUD::DrawCrossHair() 
{
    const TInterval<float> Center(Canvas->SizeX * 0.5f, Canvas->SizeY * 0.5f);

    const float HalfSize = 10.f;
    const float LineThickness = 3.f;
    const FLinearColor LineColor = FLinearColor::Green;

    DrawLine(Center.Min - HalfSize, Center.Max, Center.Min + HalfSize, Center.Max, LineColor, LineThickness);
    DrawLine(Center.Min, Center.Max - HalfSize, Center.Min, Center.Max + HalfSize, LineColor, LineThickness);
}

void AGameHUD::OnMatchStateChanged(EMatchState State)
{
}
