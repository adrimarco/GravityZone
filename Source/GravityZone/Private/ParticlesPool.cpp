// Fill out your copyright notice in the Description page of Project Settings.


#include "ParticlesPool.h"
#include "NiagaraActor.h"
#include "NiagaraComponent.h"

// Sets default values
AParticlesPool::AParticlesPool()
{
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AParticlesPool::BeginPlay()
{
	Super::BeginPlay();
	
	FreeParticleSystems.Init(nullptr, Capacity);
	UWorld* World = GetWorld();

	for (int32 i = 0; i < Capacity; i++) {
		ANiagaraActor* NewSystem = World->SpawnActor<ANiagaraActor>();
		FreeParticleSystems[i] = NewSystem;

		UNiagaraComponent* NiagaraComponent = NewSystem->GetNiagaraComponent();
		NiagaraComponent->SetAsset(NiagaraAsset);
		NiagaraComponent->bAutoActivate = false;
	}
}


ANiagaraActor* AParticlesPool::GetParticleSystemFromPool()
{
	ANiagaraActor* FreeSystem{ nullptr };

	if (!FreeParticleSystems.IsEmpty()) {
		FreeSystem = FreeParticleSystems.Pop(false);
		FreeSystem->GetNiagaraComponent()->OnSystemFinished.AddUniqueDynamic(this, &AParticlesPool::ReturnToPool);
	}

	return FreeSystem;
}

void AParticlesPool::ReturnToPool(UNiagaraComponent* FinishedNiagaraSystem)
{
	FreeParticleSystems.Emplace(Cast<ANiagaraActor>(FinishedNiagaraSystem->GetOwner()));
}
