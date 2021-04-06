// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <Components/CustomCharacterMovementComponent.h>
#include <Components/HealthComponent.h>
#include <Components/TextRenderComponent.h>
#include "..\..\Public\Player\PlayerCharacter.h"
#include <GameFramework\Controller.h>

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

    OnHealthChanged(HealthComponent->GetHealth());
    HealthComponent->OnDeath.AddUObject(this, &APlayerCharacter::OnDeath);
    HealthComponent->OnHealthChanged.AddUObject(this, &APlayerCharacter::OnHealthChanged);
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
}

void APlayerCharacter::OnHealthChanged(float NewHealth)
{
    HealthTextRender->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), NewHealth)));
}
