// Fill out your copyright notice in the Description page of Project Settings.


#include "ParticlesProviderSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "ParticlesPool.h"
#include "NiagaraActor.h"
#include "NiagaraComponent.h"


void UParticlesProviderSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
	TArray<AActor*> ParticlePoolsFound;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AParticlesPool::StaticClass(), ParticlePoolsFound);

	// Saves pool reference
	for (AActor* PoolActor : ParticlePoolsFound) {
		if (PoolActor->ActorHasTag("ShotParticles"))
			ShotParticlesSystems = Cast<AParticlesPool>(PoolActor);
	}
}

void UParticlesProviderSubsystem::SpawnShotParticles(FVector InitialLocation, FVector FinalLocation, FRotator SystemRotation)
{
	if (ShotParticlesSystems == nullptr) return;

	ANiagaraActor* ParticleSystem{ ShotParticlesSystems->GetParticleSystemFromPool() };
	if (ParticleSystem == nullptr) return;

	ParticleSystem->SetActorLocation(InitialLocation);
	ParticleSystem->SetActorRotation(SystemRotation);

	UNiagaraComponent* NiagaraComponent{ ParticleSystem->GetNiagaraComponent() };
	FVector ShotVector{ FinalLocation - InitialLocation };
	float ShotDistance = ShotVector.Length();

	NiagaraComponent->SetFloatParameter(FName("BeamLength"), FMath::Min(ShotDistance, ShotParticlesMaxLength));
	NiagaraComponent->SetFloatParameter(FName("BeamLifetime"), ShotDistance/ShotParticlesSpeed);
	NiagaraComponent->SetVectorParameter(FName("BeamDirection"), ShotVector.GetSafeNormal());
	NiagaraComponent->SetVectorParameter(FName("ImpactLocation"), FinalLocation);

	NiagaraComponent->Activate();
}
