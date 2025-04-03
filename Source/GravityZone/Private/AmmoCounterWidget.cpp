// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoCounterWidget.h"
#include "Label.h"
#include "WeaponComponent.h"

void UAmmoCounterWidget::SetLoadedAmmo(int32 Ammo)
{
	verify(LoadedAmmoLabel);
	LoadedAmmoLabel->SetText(FText::AsNumber(Ammo));
}

void UAmmoCounterWidget::SetReserveAmmo(int32 Ammo)
{
	verify(ReserveAmmoLabel);
	ReserveAmmoLabel->SetText(FText::AsNumber(Ammo));
}

void UAmmoCounterWidget::SetWeaponReference(UWeaponComponent* NewWeapon)
{
	// Remove previous weapon bindings
	if (Weapon) {
		Weapon->OnLoadedAmmoChanged.RemoveDynamic(this, &UAmmoCounterWidget::SetLoadedAmmo);
		Weapon->OnReserveAmmoChanged.RemoveDynamic(this, &UAmmoCounterWidget::SetReserveAmmo);
	}

	// Update weapon and bind events
	Weapon = NewWeapon;
	if (Weapon) {
		Weapon->OnLoadedAmmoChanged.AddDynamic(this, &UAmmoCounterWidget::SetLoadedAmmo);
		Weapon->OnReserveAmmoChanged.AddDynamic(this, &UAmmoCounterWidget::SetReserveAmmo);

		SetLoadedAmmo(Weapon->GetLoadedAmmo());
		SetReserveAmmo(Weapon->GetReserveAmmo());
		SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else {
		SetVisibility(ESlateVisibility::Collapsed);
	}
}
