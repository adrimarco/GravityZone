// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"
#include "ParticlesProviderSubsystem.h"

// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UWeaponComponent::ResetWeaponAmmo()
{
	LoadedAmmo = MagazineCapacity;
	ReserveAmmo = MaxReserveAmmo / 2;
}

void UWeaponComponent::ShotBullet()
{
	FVector ShotInitialLocation{ GetAttachParent()->GetComponentLocation() };
	FVector ShotRayEndLocation{ ShotInitialLocation + GetAttachParent()->GetForwardVector() * 20000 };
	FVector ImpactLocation;

	if (AActor* HitActor = GetShotHitActor(ShotInitialLocation, ShotRayEndLocation, ImpactLocation)) {
		UE_LOG(LogTemp, Warning, TEXT("Actor shot: %s at %f/%f/%f"), *HitActor->GetName(), ImpactLocation.X, ImpactLocation.Y, ImpactLocation.Z);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No actor hit: %f/%f/%f"), ImpactLocation.X, ImpactLocation.Y, ImpactLocation.Z);
	}
	GetWorld()->GetSubsystem<UParticlesProviderSubsystem>()->SpawnShotParticles(ShotInitialLocation, ImpactLocation, GetAttachParent()->GetComponentRotation());
}

AActor* UWeaponComponent::GetShotHitActor(FVector InitialLocation, FVector EndLocation, FVector& ImpactLocation) const
{
	FHitResult HitResult;
	if (GetWorld()->LineTraceSingleByChannel(HitResult, InitialLocation, EndLocation, ECollisionChannel::ECC_Visibility)) {
		ImpactLocation = HitResult.ImpactPoint;
		return HitResult.GetActor();
	}
	
	// No object hit
	ImpactLocation = EndLocation;
	return nullptr;
}

void UWeaponComponent::StartFiring()
{
}

void UWeaponComponent::StopFiring()
{
}

