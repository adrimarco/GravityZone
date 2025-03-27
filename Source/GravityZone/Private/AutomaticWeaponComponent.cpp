// Fill out your copyright notice in the Description page of Project Settings.


#include "AutomaticWeaponComponent.h"

// Sets default values for this component's properties
UAutomaticWeaponComponent::UAutomaticWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UAutomaticWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UAutomaticWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UAutomaticWeaponComponent::StartFiring()
{
	bIsFiring = true;
}

void UAutomaticWeaponComponent::StopFiring()
{
	bIsFiring = false;
}

void UAutomaticWeaponComponent::UpdateFireRate(float Time)
{
	Super::UpdateFireRate(Time);

	if (bIsFiring && LastShotTimer >= FireRate)
		ShotBullet();
}
