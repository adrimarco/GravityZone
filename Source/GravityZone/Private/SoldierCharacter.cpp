// Fill out your copyright notice in the Description page of Project Settings.


#include "SoldierCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GravityControllerComponent.h"
#include "WeaponComponent.h"
#include "DamageComponent.h"
#include "TimerManager.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ASoldierCharacter::ASoldierCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	FPCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FPSCamera"));
	FPCamera->SetupAttachment(GetCapsuleComponent());
	FPCamera->bUsePawnControlRotation = false;

	GravityController = CreateDefaultSubobject<UGravityControllerComponent>(TEXT("Gravity Controller"));

	DamageComponent = CreateDefaultSubobject<UDamageComponent>(TEXT("Damage Component"));
	DamageComponent->OnActorDie.AddDynamic(this, &ASoldierCharacter::Die);
}

void ASoldierCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

float ASoldierCharacter::GetPitchOffsetClampedToCameraLimit(float AddedPitch) const
{
	constexpr float MinCameraPitch{-80};
	constexpr float MaxCameraPitch{80};

	float CurrentCameraPicth = FPCamera->GetRelativeRotation().Pitch;
	float NewCameraPitch{ CurrentCameraPicth + AddedPitch };

	if (NewCameraPitch > MaxCameraPitch)
		return MaxCameraPitch - CurrentCameraPicth;
	else if (NewCameraPitch < MinCameraPitch)
		return MinCameraPitch - CurrentCameraPicth;

	return AddedPitch;
}

void ASoldierCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASoldierCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void ASoldierCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector{ Value.Get<FVector2D>() };

	// Yaw rotation is applied to actor while camera only rotates with Pitch
	AddActorLocalRotation(FRotator{ 0, LookAxisVector.X, 0 });
	FPCamera->AddLocalRotation(FRotator{ GetPitchOffsetClampedToCameraLimit(LookAxisVector.Y), 0, 0 });
}

// Called to bind functionality to input
void ASoldierCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMap, 0);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
		{
			// Jumping
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

			// Moving
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASoldierCharacter::Move);

			// Looking
			EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASoldierCharacter::Look);

			// Gravity rotation actions
			EnhancedInputComponent->BindAction(RotateGravityRightAction, ETriggerEvent::Triggered, GravityController, &UGravityControllerComponent::RotateGravityRight);
			EnhancedInputComponent->BindAction(RotateGravityLeftAction, ETriggerEvent::Triggered, GravityController, &UGravityControllerComponent::RotateGravityLeft);
			EnhancedInputComponent->BindAction(RotateGravityForwardAction, ETriggerEvent::Triggered, GravityController, &UGravityControllerComponent::RotateGravityForward);
			EnhancedInputComponent->BindAction(RotateGravityBackwardAction, ETriggerEvent::Triggered, GravityController, &UGravityControllerComponent::RotateGravityBackward);
		
			// Shot
			EnhancedInputComponent->BindAction(ShotAction, ETriggerEvent::Started, this, &ASoldierCharacter::FireWeapon);
			EnhancedInputComponent->BindAction(ShotAction, ETriggerEvent::Completed, this, &ASoldierCharacter::StopFiringWeapon);

			// Reload
			EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Triggered, this, &ASoldierCharacter::ReloadWeapon);
		}
	}
}

void ASoldierCharacter::FireWeapon()
{
	if (EquipedWeapon != nullptr)
		EquipedWeapon->StartFiring();
}

void ASoldierCharacter::StopFiringWeapon()
{
	if (EquipedWeapon != nullptr)
		EquipedWeapon->StopFiring();
}

void ASoldierCharacter::ReloadWeapon()
{
	if (EquipedWeapon != nullptr)
		EquipedWeapon->ReloadAmmo();
}

void ASoldierCharacter::Die()
{
	DisableInput(Cast<APlayerController>(Controller));
	SetActorHiddenInGame(true);
}

void ASoldierCharacter::Spawn()
{
	EnableInput(Cast<APlayerController>(Controller));
	SetActorHiddenInGame(false);
}

