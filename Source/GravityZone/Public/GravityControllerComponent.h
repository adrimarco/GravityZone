// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GravityControllerComponent.generated.h"

class ASoldierCharacter;
class UInputAction;

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChargeRecovered, int32, CurrentCharges);

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChargeLost, int32, CurrentCharges);

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMaxChargesChanged, int32, MaxCharges);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class GRAVITYZONE_API UGravityControllerComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	ASoldierCharacter* PlayerCharacter{ nullptr };

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Gravity")
	FVector TargetGravityDirection{ FVector::DownVector };

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Gravity")
	bool bIsInterpolatingGravity{ false };

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera target")
	bool bShouldCameraFollowTarget{ false };

	// Caches the distance to a detected collision point. Assumes the value remains relatively stable.
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera target")
	float CachedCameraTargetDistance{ 0 };


	// Time for recovering a charge after changing gravity.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cooldown")
	float ChargeCooldown{ 4 };

	// Remaining time for recovering a charge.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Cooldown")
	float CurrentCooldown{ 0 };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Cooldown")
	int32 CurrentCharges{ 0 };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cooldown")
	int32 MaxCharges{ 3 };

public:
	UPROPERTY(BlueprintAssignable, Category = "Delegate")
	FChargeRecovered OnChargeRecovered;

	UPROPERTY(BlueprintAssignable, Category = "Delegate")
	FChargeLost OnChargeLost;

	UPROPERTY(BlueprintAssignable, Category = "Delegate")
	FMaxChargesChanged OnMaxChargesChanged;

public:	
	// Sets default values for this component's properties
	UGravityControllerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Rotates gravity around character's forward axis
	UFUNCTION(BlueprintCallable, Category = "Gravity Change")
	void RotateGravityHorizontally(float Angle);
	
	// Rotates gravity around character's right axis
	UFUNCTION(BlueprintCallable, Category = "Gravity Change")
	void RotateGravityVertically(float Angle);

public:
	UFUNCTION(BlueprintCallable, Category = "Gravity Change")
	void RotateGravityRight();

	UFUNCTION(BlueprintCallable, Category = "Gravity Change")
	void RotateGravityLeft();

	UFUNCTION(BlueprintCallable, Category = "Gravity Change")
	void RotateGravityForward();
	
	UFUNCTION(BlueprintCallable, Category = "Gravity Change")
	void RotateGravityBackward();

	UFUNCTION(BlueprintCallable, Category = "Gravity Change")
	void RotateGravityToDefault();

	// Changes gravity direction to default direction without rotating the actor.
	UFUNCTION(BlueprintCallable, Category = "Gravity Change")
	void SetDefaultGravityDirection();

protected:
	// Updates TargetGravityDirection and enables gravity's direction interpolation.
	// Interpolating the direction causes the actor to rotate.
	UFUNCTION(BlueprintCallable, Category = "Gravity Change")
	void ChangeGravityDirection(const FVector& NewDirection);

	// Gradually updates the current gravity direction to match TargetGravityDirection.
	// Also rotates the character to align with the updated gravity direction.
	UFUNCTION(BlueprintCallable, Category = "Gravity Change")
	void InterpolateToTargetGravityDirection(float InterpolationAlpha);

	// Performs a raycast from the camera and stores the distance to the closest object in front of it.
	UFUNCTION(BlueprintCallable, Category = "Camera")
	void CacheCameraTargetDistance();

	// Rotates character and camera to face the TargetPosition.
	UFUNCTION(BlueprintCallable, Category = "Camera")
	void RotateToPosition(const FVector& TargetPosition);

	// Takes a normalized FVector and returns the closest cardinal axis to it.
	// Assumes the input vector is already normalized.
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Utility")
	static FVector GetVectorAlignedToAxis(const FVector& OriginalVector);

	// Updates cooldown variables. Recovers a charge after the time specified in ChargeCooldown.
	// Maximum number of charges is limited to MaxCharges
	inline void UpdateCooldown(float DeltaTime);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	int32 GetCurrentCharges() const { return CurrentCharges; }
	int32 GetMaxCharges() const { return MaxCharges; }

	void SetCharges(int32 NewChargesCount);
	void SetMaxCharges(int32 NewMaxChargesCount);
};
