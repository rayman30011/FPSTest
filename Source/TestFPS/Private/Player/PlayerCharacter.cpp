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
#include "Components/WidgetComponent.h"
#include "UI/HealthBarWidget.h"

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

    HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("HealthWidgetComponent");
    HealthWidgetComponent->SetupAttachment(GetRootComponent());
    HealthWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
    Super::BeginPlay();

    check(HealthComponent);
    check(GetCharacterMovement());
    check(WeaponComponent);
    check(HealthWidgetComponent);

    OnHealthChanged(HealthComponent->GetHealth(), 0.f);
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
    PlayerInputComponent->BindAction("Sprint", IE_Released, this, &APlayerCharacter::UnSprint);
    PlayerInputComponent->BindAction("Attack", IE_Pressed, WeaponComponent, &UWeaponComponent::StartFire);
    PlayerInputComponent->BindAction("Attack", IE_Released, WeaponComponent, &UWeaponComponent::StopFire);
    PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, WeaponComponent, &UWeaponComponent::NextWeapon);
    PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &UWeaponComponent::Reload);
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

void APlayerCharacter::SetPlayerColor(const FLinearColor& Color)
{
    const auto Material = GetMesh()->CreateAndSetMaterialInstanceDynamic(0);
    if (!Material) return;

    Material->SetVectorParameterValue(MaterialColorName, Color);
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

void APlayerCharacter::UnSprint()
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
    WeaponComponent->StopFire();

    GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    GetMesh()->SetSimulatePhysics(true);
}

void APlayerCharacter::OnHealthChanged(float NewHealth, float Delta)
{
    const auto Widget = Cast<UHealthBarWidget>(HealthWidgetComponent->GetUserWidgetObject());
    if (!Widget) return;

    Widget->SetHealthPercent(HealthComponent->GetHealthPercent());
}


void APlayerCharacter::OnGroundLanded(const FHitResult& Hit) 
{
    const auto VelocityZ = -GetCharacterMovement()->Velocity.Z;

    if (VelocityZ < LandedDamageVelocity.X) return;

    const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, VelocityZ);
    TakeDamage(FinalDamage, FDamageEvent{}, nullptr, nullptr);
}