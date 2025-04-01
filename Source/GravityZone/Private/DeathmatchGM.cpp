// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathmatchGM.h"
#include "Respawnable.h"
#include "WeaponFactory.h"

ADeathmatchGM::ADeathmatchGM()
{
	bStartPlayersAsSpectators = true;
}

ADeathmatchGM::~ADeathmatchGM()
{
	EnableRespawn(false);
}

void ADeathmatchGM::BeginPlay()
{
	EnableRespawn(true);

	if (WeaponFactory)
		GetWorld()->SpawnActor<AWeaponFactory>(WeaponFactory, FActorSpawnParameters{});
}

void ADeathmatchGM::RespawnPlayer(AController* PlayerController, URespawnable* RespawnableComponent)
{
	if (!RespawnableComponent->bIsWaitingToRespawn) return;

	AActor* StartActor{ ChoosePlayerStart(PlayerController) };

	if (StartActor)
		PlayerController->GetPawn()->SetActorTransform(StartActor->GetActorTransform(), false, nullptr, ETeleportType::ResetPhysics);
	else
		UE_LOG(LogTemp, Warning, TEXT("Cannot respawn player. Start actor not found."));

	RespawnableComponent->bIsWaitingToRespawn = false;
	RespawnableComponent->OnRespawn.Broadcast();
}

