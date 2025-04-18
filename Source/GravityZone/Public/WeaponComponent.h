// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

class Texture2d;
class UWeaponAnimationData;

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLoadedAmmoChangeDelegate, int32, LoadedAmmo);

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FReserveAmmoChangeDelegate, int32, ReserveAmmo);

UENUM(BlueprintType)
enum class EWeaponCategory : uint8 {
	Main,
	Secondary,
	Melee,
};

UCLASS(Abstract, ClassGroup=(Custom) )
class GRAVITYZONE_API UWeaponComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "General")
	FName Name{};

	// Weapon image to display in UI
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "General")
	TObjectPtr<UTexture2D> Image{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "General")
	EWeaponCategory Category;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation")
	TObjectPtr<UWeaponAnimationData> AnimationCollection;

	// Skeletal mesh used to represent the weapon in another perspective.
	// This mesh must stay visually synchronized with the primary mesh of this UWeaponComponent.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "General")
	TObjectPtr<USkeletalMeshComponent> MirroredMesh;

	// Reference to the component that defines the origin point for firing raycasts.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "General")
	USceneComponent* RaycasterObject;


	// Base damage dealt by each projectile when within effective range.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float ProjectileBaseDamage{ 1 };

	// Damage reduction per 100 unreal units, applied beyond the effective range.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float DamageFalloff{ 1 };


	// Maximum distance within which projectiles deal full damage.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Range")
	float EffectiveRange{ 1000 };


	// After shoting, time required to shot again.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fire rate")
	float FireRate{ 0.1f };

	// Time elapsed since last shot.
	UPROPERTY(BlueprintReadOnly, Category = "Fire rate")
	float LastShotTimer{ 0 };


	// Current amount of bullets loaded in the weapon.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ammo")
	int32 LoadedAmmo{ 0 };

	// Maximum capacity of bullets that can be loaded into the weapon.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	int32 MagazineCapacity{ 1000 };

	// Number of bullets available in reserve (not currently loaded in the weapon).
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ammo")
	int32 ReserveAmmo{ 0 };

	// Maximum number of bullets the player can carry in reserve.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	int32 MaxReserveAmmo{ 1000 };

public:
	UPROPERTY(BlueprintAssignable, Category = "Delegate")
	FLoadedAmmoChangeDelegate OnLoadedAmmoChanged;

	UPROPERTY(BlueprintAssignable, Category = "Delegate")
	FReserveAmmoChangeDelegate OnReserveAmmoChanged;

public:	
	// Sets default values for this component's properties
	UWeaponComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void ShotBullet();

	// Performs a raycast from InitialLocation to EndLocation and returns the hit actor.
	// ImpactLocation is updated with the impact position of the bullet in world space.
	// Returns nullptr if no actor is hit.
	AActor* GetActorHitByShot(FVector InitialLocation, FVector EndLocation, FVector& ImpactLocation) const;

	// Returns the damage dealt by the weapon to a target at the provided Distance
	float GetDamageByDistance(float Distance) const;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Sets LoadedAmmo and ReserveAmmo to their default values
	UFUNCTION(BlueprintCallable)
	void ResetWeaponAmmo();

	// Saves the provided USkeletalMeshComponent as MirroredMesh to keep it visually
	// synchronized with the UWeaponComponent primary mesh.
	void RegisterMirroredMesh(USkeletalMeshComponent* NewMirroredMesh);
	
	virtual void StartFiring();
	virtual void StopFiring();
	virtual void ReloadAmmo();
	virtual void UpdateFireRate(float Time);

	void SetRaycasterObject(USceneComponent* NewRaycaster);

	void SetVisibility(bool NewVisibility);

	EWeaponCategory GetCategory() const { return Category; }
	int32 GetLoadedAmmo() const { return LoadedAmmo; }
	int32 GetMagazineCapacity() const { return MagazineCapacity; }
	int32 GetReserveAmmo() const { return ReserveAmmo; }
	USkeletalMeshComponent* GetMirroredMesh() const { return MirroredMesh.Get(); }
	UWeaponAnimationData* GetAnimations() const { return AnimationCollection; }
};
