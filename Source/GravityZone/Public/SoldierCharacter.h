// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SoldierCharacter.generated.h"

class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UGravityControllerComponent;
class UDamageComponent;
class UWeaponComponent;
struct FInputActionValue;

UCLASS(config=Game)
class GRAVITYZONE_API ASoldierCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FPCamera{ nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UGravityControllerComponent* GravityController{ nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UDamageComponent* DamageComponent{ nullptr };

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UWeaponComponent* EquipedWeapon{ nullptr };

	/*
	** Input Actions
	*/

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* InputMap{ nullptr };

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction{ nullptr };
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction{ nullptr };

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction{ nullptr };

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* ShotAction{ nullptr };

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* RotateGravityRightAction{ nullptr };

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* RotateGravityLeftAction{ nullptr };

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* RotateGravityForwardAction{ nullptr };

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* RotateGravityBackwardAction{ nullptr };

public:
	// Sets default values for this character's properties
	ASoldierCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	// Takes a float representing the pitch offset to be applied to the camera's rotation.
	// Returns the adjusted value needed to avoid exceeding the camera rotation limits.
	// If the AddedPitch does not exceed the defined limits, the original value is returned.
	float GetPitchOffsetClampedToCameraLimit(float AddedPitch) const;

	void FireWeapon();
	void StopFiringWeapon();

	void Die();
	void Spawn();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Returns character's attached camera.
	UCameraComponent* GetCamera() const { return FPCamera; }
};
