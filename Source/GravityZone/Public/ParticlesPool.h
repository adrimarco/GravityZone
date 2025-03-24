// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ParticlesPool.generated.h"

class ANiagaraActor;
class UNiagaraComponent;
class UNiagaraSystem;

UCLASS()
class GRAVITYZONE_API AParticlesPool : public AActor
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<TObjectPtr<ANiagaraActor>> FreeParticleSystems{};

protected:
	// Niagara asset used in all particle systems in the pool
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UNiagaraSystem> NiagaraAsset;

	// Maximum number of active systems.
	// !! The pool creates this quantity of NiagaraActors when game starts.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "1"))
	int32 Capacity{ 100 };
	
public:	
	// Sets default values for this actor's properties
	AParticlesPool();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ReturnToPool(UNiagaraComponent* FinishedNiagaraSystem);

public:	
	UFUNCTION(BlueprintCallable)
	ANiagaraActor* GetParticleSystemFromPool();
};
