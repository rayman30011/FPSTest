// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/UI/MenuHUD.h"

#include "Blueprint/UserWidget.h"

void AMenuHUD::BeginPlay()
{
    const auto Widget = CreateWidget<UUserWidget>(GetWorld(), MenuWidgetClass);
    if (Widget)
    {
        Widget->AddToViewport();
    }
}
