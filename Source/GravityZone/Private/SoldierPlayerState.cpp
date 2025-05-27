// Fill out your copyright notice in the Description page of Project Settings.


#include "SoldierPlayerState.h"
#include "AbilitySystemComponent.h"
#include "SoldierAttributes.h"


ASoldierPlayerState::ASoldierPlayerState() {
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("Ability System"));
	USoldierAttributes* Attributes = CreateDefaultSubobject<USoldierAttributes>(TEXT("SoldierAttributes"));
	AbilitySystemComponent->AddAttributeSetSubobject(Attributes);
}

UAbilitySystemComponent* ASoldierPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
