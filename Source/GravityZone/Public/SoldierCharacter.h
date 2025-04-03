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
class URespawnable;
struct FInputActionValue;
enum class EWeaponId : uint8;

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWeaponEquipedDelegate, UWeaponComponent*, Weapon);

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
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	URespawnable* RespawnComponent{ nullptr };

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	UWeaponComponent* EquipedWeapon{ nullptr };

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	UWeaponComponent* MainWeapon{ nullptr };

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	UWeaponComponent* SecondaryWeapon{ nullptr };

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon", meta = (AllowPrivateAccess = "true"))
	UWeaponComponent* MeleeWeapon{ nullptr };

public:
	// Notifies when a new weapon is equiped.
	UPROPERTY(BlueprintAssignable, Category = "Delegate")
	FWeaponEquipedDelegate OnWeaponEquiped;

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
	UInputAction* ReloadAction{ nullptr };

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* ChangeWeaponAction{ nullptr };

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
	void ReloadWeapon();
	void ChangeEquipedWeapon();

	UFUNCTION(BlueprintCallable)
	void Die();

	UFUNCTION(BlueprintCallable)
	void Spawn();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Gives the character a weapon with the provided Id.
	UFUNCTION(BlueprintCallable)
	void AddNewWeapon(const EWeaponId& Id);

	// Checks NewWeapon category and saves its reference in the appropiate variable.
	// As soldier can hold one weapon of each type, if another weapon with the same 
	// category exists, it is destroyed.
	void SaveWeaponComponent(UWeaponComponent* NewWeapon);
	
	// Returns character's attached camera.
	UCameraComponent* GetCamera() const { return FPCamera; }
	
	// Returns character's equiped weapon.
	UWeaponComponent* GetEquipedWeapon() const { return EquipedWeapon; }

	UDamageComponent* GetDamageComponent() const { return DamageComponent; }
	UGravityControllerComponent* GetGravityController() const { return GravityController; }
};
