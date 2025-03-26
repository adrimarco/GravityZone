// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageComponent.h"

// Sets default values for this component's properties
UDamageComponent::UDamageComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UDamageComponent::BeginPlay()
{
	Super::BeginPlay();

	RecoverFullHealth();
}


// Called every frame
void UDamageComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UDamageComponent::RecoverHealth(float HealthRecovered)
{
	Health = FMath::Min(Health + HealthRecovered, MaxHealth);
}

void UDamageComponent::RecoverFullHealth()
{
	Health = MaxHealth;
}

void UDamageComponent::TakeDamage(float DamagePoints)
{
	if (Health <= 0) return;

	Health -= DamagePoints;

	if (Health <= 0) {
		OnActorDie.Broadcast();
	}
}

