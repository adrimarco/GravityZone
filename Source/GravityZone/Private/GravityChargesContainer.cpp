// Fill out your copyright notice in the Description page of Project Settings.


#include "GravityChargesContainer.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/PanelSlot.h"
#include "GravityChargeIcon.h"

void UGravityChargesContainer::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (Container) {
		SetChargesCount(ChargesCount);
	}
}

void UGravityChargesContainer::SetChargesCount(int32 NewChargesCount)
{
	if (NewChargesCount < 0) return;
	ChargesCount = NewChargesCount;

	verify(Container && GravityChargeClass);
	Container->ClearChildren();

	for (int32 i = 0; i < NewChargesCount; i++) {
		UGravityChargeIcon* NewCharge = CreateWidget<UGravityChargeIcon>(GetWorld(), GravityChargeClass);
		Container->AddChild(NewCharge);

		UHorizontalBoxSlot* ChargeSlot{ Cast<UHorizontalBoxSlot>(NewCharge->Slot) };
		ChargeSlot->SetPadding(FMargin{ 0, CalculateSlotVerticalOffset(i), 0, 0 });
		ChargeSlot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
		ChargeSlot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
	}
}

float UGravityChargesContainer::CalculateSlotVerticalOffset(float ChargeIndex)
{
	float CenterIndex{ (ChargesCount - 1) / 2.f };
	float CenterDistance{ FMath::Abs(ChargeIndex - CenterIndex)};

	return (1 - CenterDistance / CenterIndex) * MaxIconOffset;
}
