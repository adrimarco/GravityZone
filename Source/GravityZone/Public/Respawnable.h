// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Respawnable.generated.h"

DECLARE_DELEGATE_TwoParams(FRespawnRequestedDelegate, AController*, class URespawnable*);

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FRespawnDelegate);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GRAVITYZONE_API URespawnable : public UActorComponent
{
	GENERATED_BODY()

public:
	static FRespawnRequestedDelegate OnRespawnRequested;

	UPROPERTY(BlueprintAssignable)
	FRespawnDelegate OnRespawn;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsWaitingToRespawn{ false };

public:	
	// Sets default values for this component's properties
	URespawnable();

	// Execute delegate to notify RespawnManager and respawn the actor.
	// The manager must be present in world in order to work.
	void RequestRespawn(AController* Controller);
};
