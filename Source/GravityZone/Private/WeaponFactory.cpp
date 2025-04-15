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

	
UWeaponComponent* AWeaponFactory::CreateWeapon(const EWeaponId& Id, USceneComponent* ThirdPersonParent, USceneComponent* FirstPersonParent) const
{
	if (!Weapons.Contains(Id) || ThirdPersonParent == nullptr) return nullptr;

	TSubclassOf<UWeaponComponent> WeaponClass{ Weapons[Id] };
	if (WeaponClass == nullptr) return nullptr;

	UWeaponComponent* NewWeapon{ NewObject<UWeaponComponent>(ThirdPersonParent->GetOwner(), WeaponClass) };
	NewWeapon->SetupAttachment(ThirdPersonParent, FName(TEXT("weapon_grip")));
	NewWeapon->RegisterComponent();

	NewWeapon->SetOwnerNoSee(true);
	NewWeapon->SetCastShadow(true);


	if (FirstPersonParent) {
		USkeletalMeshComponent* MirroredMesh{ NewObject<USkeletalMeshComponent>(FirstPersonParent->GetOwner()) };
		MirroredMesh->SetupAttachment(FirstPersonParent, FName(TEXT("weapon_grip")));
		MirroredMesh->RegisterComponent();
		FirstPersonParent->GetOwner()->AddInstanceComponent(MirroredMesh);

		NewWeapon->RegisterMirroredMesh(MirroredMesh);

		MirroredMesh->SetOnlyOwnerSee(true);
		MirroredMesh->SetCastShadow(false);
	}
	
	return NewWeapon;
}

