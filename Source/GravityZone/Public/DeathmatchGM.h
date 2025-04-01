// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "RespawnManager.h"
#include "DeathmatchGM.generated.h"

class URespawnable;
class AWeaponFactory;

UCLASS()
class GRAVITYZONE_API ADeathmatchGM : public AGameMode, public IRespawnManager
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AWeaponFactory> WeaponFactory{};

public:
	ADeathmatchGM();

	virtual ~ADeathmatchGM();

protected:
	virtual void BeginPlay() override;
	//virtual void OnPostLogin(AController* NewPlayer) override;

	UFUNCTION(BlueprintCallable)
	virtual void RespawnPlayer(AController* PlayerController, URespawnable* RespawnableComponent) override;
};
