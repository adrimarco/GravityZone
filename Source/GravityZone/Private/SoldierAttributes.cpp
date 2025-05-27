// Fill out your copyright notice in the Description page of Project Settings.


#include "SoldierAttributes.h"

USoldierAttributes::USoldierAttributes()
{
	MovementSpeed = 450;
}

bool USoldierAttributes::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	return false;
}

void USoldierAttributes::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
}
