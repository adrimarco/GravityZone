// Fill out your copyright notice in the Description page of Project Settings.


#include "SoldierPlayerState.h"
#include "AbilitySystemComponent.h"


ASoldierPlayerState::ASoldierPlayerState() {
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("Ability System"));
}

UAbilitySystemComponent* ASoldierPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
