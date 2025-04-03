// Fill out your copyright notice in the Description page of Project Settings.


#include "SoldierHUD.h"
#include "SoldierCharacter.h"
#include "HealthDisplayWidget.h"
#include "AmmoCounterWidget.h"
#include "GravityChargesContainer.h"
#include "Components/Image.h"
#include "WeaponComponent.h"
#include "DamageComponent.h"
#include "GravityControllerComponent.h"

void USoldierHUD::BindToSoldierCharacter(ASoldierCharacter* Character)
{
	if (Character == nullptr) return;

	// Weapon data
	if(UWeaponComponent* EquipedWeapon = Character->GetEquipedWeapon()) {
		AmmoCounter->SetWeaponReference(EquipedWeapon);
	}
	Character->OnWeaponEquiped.AddDynamic(AmmoCounter, &UAmmoCounterWidget::SetWeaponReference);
	
	// Health
	UDamageComponent* DamageComponent{ Character->GetDamageComponent() };
	HealthDisplay->SetHealth(DamageComponent->GetHealth(), DamageComponent->GetMaxHealth());
	DamageComponent->OnActorDamaged.AddDynamic(HealthDisplay, &UHealthDisplayWidget::SetHealth);
	DamageComponent->OnActorHealed.AddDynamic(HealthDisplay, &UHealthDisplayWidget::SetHealth);

	// Gravity
	UGravityControllerComponent* GravityController{ Character->GetGravityController() };
	GravityChargesDisplay->SetChargesCount(3);
}
