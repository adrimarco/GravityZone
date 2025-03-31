// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponFactory.h"
#include "WeaponComponent.h"

AWeaponFactory* AWeaponFactory::Instance{ nullptr };

// Sets default values
AWeaponFactory::AWeaponFactory()
{
	PrimaryActorTick.bCanEverTick = false;
}

AWeaponFactory::~AWeaponFactory()
{
	if (Instance == this)
		Instance = nullptr;
}

// Called when the game starts or when spawned
void AWeaponFactory::BeginPlay()
{
	Super::BeginPlay();
	
	if (Instance == nullptr)
		Instance = this;
	else
		Destroy();
}

	
UWeaponComponent* AWeaponFactory::CreateWeapon(const EWeaponId& Id, USceneComponent* NewWeaponParent) const
{
	if (!Weapons.Contains(Id) || NewWeaponParent == nullptr) return nullptr;

	TSubclassOf<UWeaponComponent> WeaponClass{ Weapons[Id] };
	if (WeaponClass == nullptr) return nullptr;

	UWeaponComponent* NewWeapon{ NewObject<UWeaponComponent>(NewWeaponParent->GetOwner(), WeaponClass) };
	NewWeapon->SetupAttachment(NewWeaponParent);
	NewWeapon->RegisterComponent();
	
	return NewWeapon;
}

