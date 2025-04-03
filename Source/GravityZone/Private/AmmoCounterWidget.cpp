// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoCounterWidget.h"
#include "Label.h"

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
