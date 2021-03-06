// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UHealthComponent;
class UTextRenderComponent;
class UWeaponComponent;
class UWidgetComponent;

UCLASS()
class TESTFPS_API APlayerCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    APlayerCharacter(const FObjectInitializer& ObjInit);

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent* Camera;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USpringArmComponent* SpringArm;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UHealthComponent* HealthComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UWeaponComponent* WeaponComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UWidgetComponent* HealthWidgetComponent;

    UPROPERTY(EditDefaultsOnly, Category = "Animations")
    UAnimMontage* DeathAnimation;

    UPROPERTY(EditAnywhere, Category = "Movement")
    FVector2D LandedDamageVelocity = FVector2D(900.f, 1200.f);

    UPROPERTY(EditAnywhere, Category = "Movement")
    FVector2D LandedDamage = FVector2D(10.f, 100.f);

    UPROPERTY(EditDefaultsOnly, Category = "Material")
    FName MaterialColorName = "BodyColor";
    
    virtual void OnDeath();

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UFUNCTION(BlueprintCallable, Category = "Movement")
    bool IsRunning() const;

    UFUNCTION(BlueprintCallable, Category = "Movement")
    float GetMovementDirection() const;

    void SetPlayerColor(const FLinearColor& Color);

private:
    bool WantsToRun = false;
    bool IsRunForward = false;

    void MoveForward(float Value);
    void MoveRight(float Value);

    void Sprint();
    void UnSprint();
    void OnHealthChanged(float NewHealth, float Delta);

    UFUNCTION()
    void OnGroundLanded(const FHitResult& Hit);
};
