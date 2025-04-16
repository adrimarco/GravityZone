// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponComponent.h"
#include "ParticlesProviderSubsystem.h"
#include "DamageComponent.h"

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

	ResetWeaponAmmo();
}


// Called every frame
void UWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateFireRate(DeltaTime);
}

void UWeaponComponent::ResetWeaponAmmo()
{
	LoadedAmmo = MagazineCapacity;
	ReserveAmmo = MaxReserveAmmo / 2;

	OnLoadedAmmoChanged.Broadcast(LoadedAmmo);
	OnReserveAmmoChanged.Broadcast(ReserveAmmo);
}

void UWeaponComponent::RegisterMirroredMesh(USkeletalMeshComponent* NewMirroredMesh)
{
	if (NewMirroredMesh == nullptr) return;

	MirroredMesh = NewMirroredMesh;

	// Synchronizes properties to visually match primary mesh
	MirroredMesh->SetSkeletalMeshAsset(GetSkeletalMeshAsset());
}

void UWeaponComponent::ShotBullet()
{
	check(RaycasterObject);

	if (LastShotTimer < FireRate) return;

	if (LoadedAmmo <= 0) {
		ReloadAmmo();
		return;
	}

	// Raycast trace to detect actors hit by the shot
	FVector ShotInitialLocation{ RaycasterObject->GetComponentLocation()};
	FVector ShotRayEndLocation{ ShotInitialLocation + RaycasterObject->GetForwardVector() * 20000 };
	FVector ImpactLocation;

	if (AActor* HitActor = GetActorHitByShot(ShotInitialLocation, ShotRayEndLocation, ImpactLocation)) {
		if (UDamageComponent* HitActorDamageComp = HitActor->GetComponentByClass<UDamageComponent>()) {
			float DistanceToHitActor = FVector::Distance(ShotInitialLocation, ImpactLocation);
			HitActorDamageComp->TakeDamage(GetDamageByDistance(DistanceToHitActor));
		}
	}

	// Particle effects
	GetWorld()->GetSubsystem<UParticlesProviderSubsystem>()->SpawnShotParticles(ShotInitialLocation, ImpactLocation, RaycasterObject->GetComponentRotation());

	LoadedAmmo--;
	LastShotTimer = 0;
	OnLoadedAmmoChanged.Broadcast(LoadedAmmo);
}

AActor* UWeaponComponent::GetActorHitByShot(FVector InitialLocation, FVector EndLocation, FVector& ImpactLocation) const
{
	FCollisionQueryParams QueryParams = FCollisionQueryParams::DefaultQueryParam;
	QueryParams.AddIgnoredActor(GetOwner());

	FHitResult HitResult;
	if (GetWorld()->LineTraceSingleByChannel(HitResult, InitialLocation, EndLocation, ECollisionChannel::ECC_Camera, QueryParams)) {
		ImpactLocation = HitResult.ImpactPoint;
		return HitResult.GetActor();
	}
	
	// No object hit
	ImpactLocation = EndLocation;
	return nullptr;
}

float UWeaponComponent::GetDamageByDistance(float Distance) const
{
	float Damage{ ProjectileBaseDamage };
	if (Distance > EffectiveRange)
		Damage = FMath::Max(1, Damage - (Distance - EffectiveRange) / 100 * DamageFalloff);

	return Damage;
}

void UWeaponComponent::ReloadAmmo()
{
	if (LoadedAmmo >= MagazineCapacity) return;

	int32 AmmoToLoad{ FMath::Min(MagazineCapacity - LoadedAmmo, ReserveAmmo) };

	LoadedAmmo += AmmoToLoad;
	ReserveAmmo -= AmmoToLoad;

	OnLoadedAmmoChanged.Broadcast(LoadedAmmo);
	OnReserveAmmoChanged.Broadcast(ReserveAmmo);
}

void UWeaponComponent::UpdateFireRate(float Time)
{
	if (LastShotTimer < FireRate)
		LastShotTimer += Time;
}

void UWeaponComponent::SetRaycasterObject(USceneComponent* NewRaycaster)
{
	RaycasterObject = NewRaycaster;
}

void UWeaponComponent::StartFiring()
{
}

void UWeaponComponent::StopFiring()
{
}

