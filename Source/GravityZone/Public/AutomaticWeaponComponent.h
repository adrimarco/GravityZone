// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponComponent.h"
#include "AutomaticWeaponComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), Blueprintable)
class GRAVITYZONE_API UAutomaticWeaponComponent : public UWeaponComponent
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly)
	bool bIsFiring{ false };

public:
	// Sets default values for this component's properties
	UAutomaticWeaponComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void StartFiring() override;
	virtual void StopFiring() override;
	virtual void UpdateFireRate(float Time) override;
};
