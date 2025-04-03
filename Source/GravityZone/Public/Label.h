// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Label.generated.h"

class UTextBlock;

UCLASS()
class GRAVITYZONE_API ULabel : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float FontSize{ 24 };
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Skew{ 0.3f };

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText LabelText{ FText::FromString("Label text") };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets", meta = (BindWidget))
	UTextBlock* TextWidget{ nullptr };

protected:
	virtual void NativePreConstruct() override;

public:
	UFUNCTION(BlueprintCallable)
	void SetFontSize(float NewFontSize);

	UFUNCTION(BlueprintCallable)
	void SetSkew(float NewSkew);

	UFUNCTION(BlueprintCallable)
	void SetText(const FText& NewText);
};
