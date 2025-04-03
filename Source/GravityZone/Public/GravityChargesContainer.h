// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GravityChargesContainer.generated.h"

class UGravityChargeIcon;
class UHorizontalBox;

UCLASS()
class GRAVITYZONE_API UGravityChargesContainer : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGravityChargeIcon> GravityChargeClass{ nullptr };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets", meta = (BindWidget))
	UHorizontalBox* Container{ nullptr };

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 ChargesCount{ 3 };

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxIconOffset{ 12.f };

protected:
	virtual void NativePreConstruct() override;

public:
	UFUNCTION(BlueprintCallable)
	void SetChargesCount(int32 NewChargesCount);

	// Calculates and returns the vertical offset for a container's child at the provided 
	// ChargeIndex based on its position in the container, which depends on ChargesCount.
	// The offset maximum at center and is defined by MaxIconOffset.
	float CalculateSlotVerticalOffset(float ChargeIndex);
};
