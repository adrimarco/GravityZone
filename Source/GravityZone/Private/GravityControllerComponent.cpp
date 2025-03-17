// Fill out your copyright notice in the Description page of Project Settings.


#include "GravityControllerComponent.h"
#include "SoldierCharacter.h"

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

	Player = Cast<ASoldierCharacter>(GetOwner());
}

// Called every frame
void UGravityControllerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

/*
* Given a FVector, returns the closest axis to the vector. Assumes normalized vector.
*/
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
	FVector ForwardAxis = GetVectorAlignedToAxis(Player->GetActorForwardVector());
	FVector NewDirection = TargetGravityDirection.RotateAngleAxis(Angle, ForwardAxis);

	ChangeGravityDirection(NewDirection);
}

void UGravityControllerComponent::RotateGravityVertically(float Angle)
{
	FVector ForwardAxis = GetVectorAlignedToAxis(Player->GetActorRightVector());
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
}
