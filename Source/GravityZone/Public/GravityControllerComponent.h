// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GravityControllerComponent.generated.h"

class ASoldierCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class GRAVITYZONE_API UGravityControllerComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	FVector TargetGravityDirection{ FVector::DownVector };

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
	ASoldierCharacter* Player{ nullptr };

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsInterpolatingGravity{ false };

public:	
	// Sets default values for this component's properties
	UGravityControllerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Gravity Change")
	void RotateGravityHorizontally(float Angle);
	
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

	UFUNCTION(BlueprintCallable, Category = "Gravity Change")
	void ChangeGravityDirection(const FVector& NewDirection);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Utility")
	static FVector GetVectorAlignedToAxis(const FVector& OriginalVector);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
