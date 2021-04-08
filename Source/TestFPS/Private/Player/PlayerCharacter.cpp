// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/PlayerCharacter.h"
#include <Components/CustomCharacterMovementComponent.h>
#include <Components/HealthComponent.h>
#include <Components/TextRenderComponent.h>
#include <GameFramework/Controller.h>
#include "Camera/CameraComponent.h"
#include "Components/WeaponComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CapsuleComponent.h"

DEFINE_LOG_CATEGORY_STATIC(CharacterLog, All, All);

// Sets default values
APlayerCharacter::APlayerCharacter(const FObjectInitializer& ObjInit)
    : Super(ObjInit.SetDefaultSubobjectClass<UCustomCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
    SpringArm->SetupAttachment(GetRootComponent());
    SpringArm->bUsePawnControlRotation = true;

    Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
    Camera->SetupAttachment(SpringArm);

    UCharacterMovementComponent* Movement = GetCharacterMovement();

    HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
    WeaponComponent = CreateDefaultSubobject<UWeaponComponent>("WeaponComponent");

    HealthTextRender = CreateDefaultSubobject<UTextRenderComponent>("HealthTextRender");
    HealthTextRender->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
    Super::BeginPlay();

    check(HealthComponent);
    check(GetCharacterMovement());
    check(HealthTextRender);
    check(WeaponComponent);

    OnHealthChanged(HealthComponent->GetHealth());
    HealthComponent->OnDeath.AddUObject(this, &APlayerCharacter::OnDeath);
    HealthComponent->OnHealthChanged.AddUObject(this, &APlayerCharacter::OnHealthChanged);

    LandedDelegate.AddDynamic(this, &APlayerCharacter::OnGroundLanded);
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

    PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::AddControllerYawInput);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::Jump);
    PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &APlayerCharacter::Sprint);
    PlayerInputComponent->BindAction("Sprint", IE_Released, this, &APlayerCharacter::Unsprint);
    PlayerInputComponent->BindAction("Attack", IE_Pressed, WeaponComponent, &UWeaponComponent::Fire);
}

bool APlayerCharacter::IsRunning() const
{
    return WantsToRun && IsRunForward && !GetVelocity().IsZero();
}

float APlayerCharacter::GetMovementDirection() const
{
    if (GetVelocity().IsZero()) return 0.f;

    auto const VelocityNormal = GetVelocity().GetSafeNormal();
    auto const AngleBeetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
    auto const Cross = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);

    return FMath::RadiansToDegrees(AngleBeetween) * FMath::Sign(Cross.Z);
}

void APlayerCharacter::MoveForward(float Value)
{
    IsRunForward = Value > 0.f;
    AddMovementInput(GetActorForwardVector(), Value);
}

void APlayerCharacter::MoveRight(float Value)
{
    AddMovementInput(GetActorRightVector(), Value);
}

void APlayerCharacter::Sprint()
{
    WantsToRun = true;
}

void APlayerCharacter::Unsprint()
{
    WantsToRun = false;
}

void APlayerCharacter::OnDeath()
{
    UE_LOG(CharacterLog, Display, TEXT("Player %s is dead"), *GetName());

    PlayAnimMontage(DeathAnimation);

    GetCharacterMovement()->DisableMovement();
    SetLifeSpan(5.0f);

    if (Controller)
    {
        Controller->ChangeState(NAME_Spectating);
    }
    
    const auto Capsule = GetCapsuleComponent();
    Capsule->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
}

void APlayerCharacter::OnHealthChanged(float NewHealth)
{
    HealthTextRender->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), NewHealth)));
}


void APlayerCharacter::OnGroundLanded(const FHitResult& Hit) 
{
    const auto VelocityZ = -GetCharacterMovement()->Velocity.Z;

    if (VelocityZ < LandedDamageVelocity.X) return;

    const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, VelocityZ);
    TakeDamage(FinalDamage, FDamageEvent{}, nullptr, nullptr);
}