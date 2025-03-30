// Fill out your copyright notice in the Description page of Project Settings.


#include "Respawnable.h"

FRespawnRequestedDelegate URespawnable::OnRespawnRequested;

// Sets default values for this component's properties
URespawnable::URespawnable()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void URespawnable::RequestRespawn(AController* Controller)
{
	if (Controller && !bIsWaitingToRespawn) {
		bIsWaitingToRespawn = true;
		OnRespawnRequested.ExecuteIfBound(Controller, this);
	}
}

