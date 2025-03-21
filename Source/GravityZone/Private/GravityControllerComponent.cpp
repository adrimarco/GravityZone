// Fill out your copyright notice in the Description page of Project Settings.


#include "GravityControllerComponent.h"
#include "SoldierCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"

// Sets default values for this component's properties
UGravityControllerComponent::UGravityControllerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGravityControllerComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<ASoldierCharacter>(GetOwner());
}


// Called every frame
void UGravityControllerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	constexpr float InterpolationSpeed{ 5 };

	InterpolateToTargetGravityDirection(DeltaTime * InterpolationSpeed);
}

FVector UGravityControllerComponent::GetVectorAlignedToAxis(const FVector& OriginalVector)
{
	// X axis
	if (OriginalVector.X > 0.5)
		return FVector::ForwardVector;
	else if (OriginalVector.X < -0.5)
		return FVector::BackwardVector;

	// Y axis
	else if (OriginalVector.Y > 0.5)
		return FVector::RightVector;
	else if (OriginalVector.Y < -0.5)
		return FVector::LeftVector;

	// Z axis
	else if (OriginalVector.Z > 0.5)
		return FVector::UpVector;
	else if (OriginalVector.Z < -0.5)
		return FVector::DownVector;

	return OriginalVector;
}

void UGravityControllerComponent::RotateGravityHorizontally(float Angle)
{
	FVector ForwardAxis = GetVectorAlignedToAxis(PlayerCharacter->GetActorForwardVector());
	FVector NewDirection = TargetGravityDirection.RotateAngleAxis(Angle, ForwardAxis);

	ChangeGravityDirection(NewDirection);
}

void UGravityControllerComponent::RotateGravityVertically(float Angle)
{
	FVector ForwardAxis = GetVectorAlignedToAxis(PlayerCharacter->GetActorRightVector());
	FVector NewDirection = TargetGravityDirection.RotateAngleAxis(Angle, ForwardAxis);

	ChangeGravityDirection(NewDirection);
}

void UGravityControllerComponent::RotateGravityRight()
{
	RotateGravityHorizontally(90);
}

void UGravityControllerComponent::RotateGravityLeft()
{
	RotateGravityHorizontally(-90);
}

void UGravityControllerComponent::RotateGravityForward()
{
	RotateGravityVertically(-90);
}

void UGravityControllerComponent::RotateGravityBackward()
{
	RotateGravityVertically(90);
}

void UGravityControllerComponent::ChangeGravityDirection(const FVector& NewDirection)
{
	TargetGravityDirection = NewDirection;
	bIsInterpolatingGravity = true;

	CacheCameraTargetDistance();
	bShouldCameraFollowTarget = true;
}

void UGravityControllerComponent::InterpolateToTargetGravityDirection(float InterpolationAlpha)
{
	if (!bIsInterpolatingGravity) return;

	FVector CameraTargetPosition{ FVector::ZeroVector };
	if (bShouldCameraFollowTarget) {
		UCameraComponent* PlayerCamera{ PlayerCharacter->GetCamera() };
		CameraTargetPosition = PlayerCamera->GetComponentLocation() + PlayerCamera->GetForwardVector() * CachedCameraTargetDistance;
	}

	UCharacterMovementComponent* CharacterMovement{ PlayerCharacter->GetCharacterMovement() };
	FVector PreviousGravityDirection{ CharacterMovement->GetGravityDirection() };
	FVector InterpolatedGravityDirection {TargetGravityDirection};

	if (PreviousGravityDirection.Equals(TargetGravityDirection, 0.01)) {
		bIsInterpolatingGravity = false;
	}
	else {
		InterpolatedGravityDirection = FVector::SlerpNormals(PreviousGravityDirection, TargetGravityDirection, InterpolationAlpha);
	}

	CharacterMovement->SetGravityDirection(InterpolatedGravityDirection);
	PlayerCharacter->AddActorWorldRotation(FQuat::FindBetweenNormals(PreviousGravityDirection, InterpolatedGravityDirection));

	if (bShouldCameraFollowTarget) {
		RotateToPosition(CameraTargetPosition);
	}
}

void UGravityControllerComponent::CacheCameraTargetDistance()
{
	constexpr float MinTargetDistance{ 300 };
	constexpr float MaxTargetDistance{ 10000 };

	FHitResult HitResult;
	UCameraComponent* PlayerCamera{ PlayerCharacter->GetCamera() };
	FVector LineTraceEndPoint{ PlayerCamera->GetComponentLocation() + PlayerCamera->GetForwardVector() * MaxTargetDistance };

	// If raycast hits an object, saves the distance to the object
	if (GetWorld()->LineTraceSingleByChannel(HitResult, PlayerCamera->GetComponentLocation(), LineTraceEndPoint, ECollisionChannel::ECC_Visibility)) {
		CachedCameraTargetDistance = FMath::Max(MinTargetDistance, HitResult.Distance);
	}
	else {
		CachedCameraTargetDistance = MaxTargetDistance;
	}
}

void UGravityControllerComponent::RotateToPosition(const FVector& TargetPosition)
{
	UCameraComponent* PlayerCamera{ PlayerCharacter->GetCamera() };
	FVector LookDirection{ (TargetPosition - PlayerCamera->GetComponentLocation()) };
	LookDirection.Normalize();

	// Converts from world-space to character's local-space coordinates
	LookDirection = PlayerCharacter->GetTransform().InverseTransformVector(LookDirection);

	FRotator TargetRotation{ FQuat::FindBetweenNormals(FVector::XAxisVector, LookDirection).Rotator()};
	FRotator AddedRotation{ (TargetRotation - PlayerCamera->GetRelativeRotation()).GetNormalized()};
	
	PlayerCharacter->AddActorLocalRotation(FRotator(0, AddedRotation.Yaw, 0));
	PlayerCamera->AddRelativeRotation(FRotator(AddedRotation.Pitch, 0, 0));
}
