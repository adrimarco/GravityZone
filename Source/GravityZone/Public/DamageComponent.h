// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DamageComponent.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FActorDieDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GRAVITYZONE_API UDamageComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health")
	float Health{ 0 };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health", meta = (ClampMin = "1"))
	float MaxHealth{ 100 };

public:
	UPROPERTY(BlueprintAssignable, Category = "Delegate")
	FActorDieDelegate OnActorDie;

public:	
	// Sets default values for this component's properties
	UDamageComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Increases the current Health by HealthRecovered, ensuring it does not exceed MaxHealth.
	UFUNCTION(BlueprintCallable)
	void RecoverHealth(float HealthRecovered);

	// Sets current Health to MaxHealth.
	UFUNCTION(BlueprintCallable)
	void RecoverFullHealth();
	
	// Decreases the current Health by DamagePoints. If Health drops to 0, triggers dying events.
	UFUNCTION(BlueprintCallable)
	void TakeDamage(float DamagePoints);

	float GetHealth() const { return Health; }
	float GetMaxHealth() const { return MaxHealth; }
};
