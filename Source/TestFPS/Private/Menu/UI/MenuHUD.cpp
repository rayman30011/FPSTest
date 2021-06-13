// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/UI/MenuHUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/BaseWidget.h"

void AMenuHUD::BeginPlay()
{
    const auto Widget = CreateWidget<UBaseWidget>(GetWorld(), MenuWidgetClass);
    if (Widget)
    {
        Widget->AddToViewport();
        Widget->Show();
    }
}
