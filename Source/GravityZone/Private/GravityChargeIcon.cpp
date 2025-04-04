// Fill out your copyright notice in the Description page of Project Settings.


#include "GravityChargeIcon.h"
#include "Components/Border.h"

void UGravityChargeIcon::NativePreConstruct()
{
	Super::NativePreConstruct();

	UpdateStyle();
}

void UGravityChargeIcon::UpdateStyle()
{
	verify(Icon);

	Icon->SetRenderOpacity(bAvailable ? 1 : 0.2f);
}

void UGravityChargeIcon::SetAvailable(bool bNewState)
{
	if (bAvailable != bNewState) {
		bAvailable = bNewState;
		UpdateStyle();
	}
}
