// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"


UCLASS(Abstract, ClassGroup=(Custom) )
class GRAVITYZONE_API UWeaponComponent : public USceneComponent
{
	GENERATED_BODY()

protected:
	// Base damage dealt by each projectile when within effective range.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float ProjectileBaseDamage{ 1 };

	// Damage reduction per 100 unreal units, applied beyond the effective range.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	float DamageFalloff{ 1 };


	// Maximum distance within which projectiles deal full damage.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Range")
	float EffectiveRange{ 1000 };


	// Current amount of bullets loaded in the weapon.
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ammo")
	int32 LoadedAmmo{ MagazineCapacity };

	// Maximum capacity of bullets that can be loaded into the weapon.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	int32 MagazineCapacity{ 1000 };

	// Number of bullets available in reserve (not currently loaded in the weapon).
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ammo")
	int32 ReserveAmmo{ 1000 };

	// Maximum number of bullets the player can carry in reserve.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	int32 MaxReserveAmmo{ 1000 };

	
public:	
	// Sets default values for this component's properties
	UWeaponComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Sets LoadedAmmo and ReserveAmmo to their default values
	UFUNCTION(BlueprintCallable)
	void ResetWeaponAmmo();
	
	virtual void StartFiring();
	virtual void StopFiring();
};
