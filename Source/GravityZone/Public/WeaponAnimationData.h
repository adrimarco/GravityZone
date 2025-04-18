// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WeaponAnimationData.generated.h"

UCLASS()
class GRAVITYZONE_API UWeaponAnimationData : public UDataAsset
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimMontage* Idle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimMontage* Aim;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimMontage* Run;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimMontage* Equip;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimMontage* Fire;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimMontage* Reload;
};
