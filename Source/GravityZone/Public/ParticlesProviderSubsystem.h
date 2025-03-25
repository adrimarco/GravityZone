// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ParticlesProviderSubsystem.generated.h"

class AParticlesPool;

/**
 * When World begins, gets all references to particle pools required for shoting and stores them.
 * It provides functions to easily use them.
 */
UCLASS()
class GRAVITYZONE_API UParticlesProviderSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

	static constexpr float ShotParticlesMaxLength{ 300 };
	static constexpr float ShotParticlesSpeed{ 20000 };

protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AParticlesPool> ShotParticlesSystems{ nullptr };
	
public:
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;

	UFUNCTION(BlueprintCallable)
	void SpawnShotParticles(FVector InitialLocation, FVector FinalLocation, FRotator SystemRotation);
};
