// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GravityControllerComponent.generated.h"

class ASoldierCharacter;
class UInputAction;

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

	/* Caches the distance to a detected collision point. Assumes the value remains relatively stable. */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Camera target")
	float CachedCameraTargetDistance{ 0 };

	/*
	** Input Actions
	*/

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Input")
	UInputAction* RotateGravityRightAction{ nullptr };

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Input")
	UInputAction* RotateGravityLeftAction{ nullptr };

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Input")
	UInputAction* RotateGravityForwardAction{ nullptr };

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Input")
	UInputAction* RotateGravityBackwardAction{ nullptr };

public:	
	// Sets default values for this component's properties
	UGravityControllerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(Category = "Input")
	void BindInputActions(UInputComponent* PlayerInputComponent);

	/* Rotates gravity around character's forward axis */
	UFUNCTION(BlueprintCallable, Category = "Gravity Change")
	void RotateGravityHorizontally(float Angle);
	
	/* Rotates gravity around character's right axis */
	UFUNCTION(BlueprintCallable, Category = "Gravity Change")
	void RotateGravityVertically(float Angle);

	UFUNCTION(BlueprintCallable, Category = "Gravity Change")
	void RotateGravityRight();

	UFUNCTION(BlueprintCallable, Category = "Gravity Change")
	void RotateGravityLeft();

	UFUNCTION(BlueprintCallable, Category = "Gravity Change")
	void RotateGravityForward();
	
	UFUNCTION(BlueprintCallable, Category = "Gravity Change")
	void RotateGravityBackward();

	/* Updates TargetGravityDirection and enables gravity's direction interpolation */
	UFUNCTION(BlueprintCallable, Category = "Gravity Change")
	void ChangeGravityDirection(const FVector& NewDirection);

	/* Gradually updates the current gravity direction to match TargetGravityDirection.
	*  Also rotates the character to align with the updated gravity direction.
	*/
	UFUNCTION(BlueprintCallable, Category = "Gravity Change")
	void InterpolateToTargetGravityDirection(float InterpolationAlpha);

	/* Performs a raycast from the camera and stores the distance to the collision directly in front of it. */
	UFUNCTION(BlueprintCallable, Category = "Camera")
	void CacheCameraTargetDistance();

	/* Rotates character and camera to face the TargetPosition */
	UFUNCTION(BlueprintCallable, Category = "Camera")
	void RotateToPosition(const FVector& TargetPosition);

	/* Takes a normalized FVector and returns the closest cardinal axis to it.
	*  Assumes the input vector is already normalized.
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Utility")
	static FVector GetVectorAlignedToAxis(const FVector& OriginalVector);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
