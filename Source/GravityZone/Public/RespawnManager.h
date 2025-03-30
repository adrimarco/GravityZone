// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "RespawnManager.generated.h"

class URespawnable;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class URespawnManager : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GRAVITYZONE_API IRespawnManager
{
	GENERATED_BODY()

public:
	// Bind the URespawnable delegate to respawn actors when it is requested.
	// Must be enabled/disabled when creating and destroying the object.
	void EnableRespawn(bool bActbNewActiveStateive);

	// Respawn logic. Must be implemented in each child class.
	virtual void RespawnPlayer(AController* PlayerController, URespawnable* RespawnComponent) = 0;
};
