// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponFactory.generated.h"

class UWeaponComponent;

UENUM(BlueprintType)
enum class EWeaponId : uint8 {
	Default,
	Glock,
	AK,
};


UCLASS()
class GRAVITYZONE_API AWeaponFactory : public AActor
{
	GENERATED_BODY()
	
protected:
	static AWeaponFactory* Instance;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<EWeaponId, TSubclassOf<UWeaponComponent>> Weapons{};

public:	
	// Sets default values for this actor's properties
	AWeaponFactory();

	virtual ~AWeaponFactory();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Creates a new UWeaponComponent from the provided Id. The component is attached to ThirdPersonParent.
	// A second mesh used in first-person view is created and attached to FirsPersonParent.
	// The Id with its associated UWeaponComponent must be present in the factory instance's map.
	// Returns nullptr if cannot create the component.
	UWeaponComponent* CreateWeapon(const EWeaponId& Id, USceneComponent* ThirdPersonParent, USceneComponent* FirstPersonParent) const;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static AWeaponFactory* GetInstance() { return Instance; };
};
