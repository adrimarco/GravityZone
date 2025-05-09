// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "SoldierPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class GRAVITYZONE_API ASoldierPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	UAbilitySystemComponent* AbilitySystemComponent{ nullptr };

public:
	ASoldierPlayerState();

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
};
