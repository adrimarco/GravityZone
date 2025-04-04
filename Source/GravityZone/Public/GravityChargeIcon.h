// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GravityChargeIcon.generated.h"

class UBorder;

UCLASS()
class GRAVITYZONE_API UGravityChargeIcon : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bAvailable{ true };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets", meta = (BindWidget))
	UBorder* Icon{ nullptr };
	
protected:
	virtual void NativePreConstruct() override;

	// Changes icon's visual style depending on whether it is available or not.
	void UpdateStyle();

public:
	void SetAvailable(bool bNewState);
};
