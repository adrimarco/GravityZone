// Fill out your copyright notice in the Description page of Project Settings.


#include "SemiAutomaticWeaponComponent.h"

// Sets default values for this component's properties
USemiAutomaticWeaponComponent::USemiAutomaticWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void USemiAutomaticWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void USemiAutomaticWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void USemiAutomaticWeaponComponent::StartFiring()
{
	ShotBullet();
}

