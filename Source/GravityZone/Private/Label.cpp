// Fill out your copyright notice in the Description page of Project Settings.


#include "Label.h"
#include "Components/TextBlock.h"

void ULabel::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (TextWidget) {
		SetFontSize(FontSize);
		SetSkew(Skew);
		SetText(LabelText);
	}
}

void ULabel::SetFontSize(float NewFontSize)
{
	if (NewFontSize <= 0) return;
	FontSize = NewFontSize;

	verify(TextWidget);
	FSlateFontInfo TextFont{ TextWidget->GetFont() };
	TextFont.Size = FontSize;
	TextWidget->SetFont(TextFont);
}

void ULabel::SetSkew(float NewSkew)
{
	Skew = NewSkew;

	verify(TextWidget);
	FSlateFontInfo TextFont{ TextWidget->GetFont() };
	TextFont.SkewAmount = Skew;
	TextWidget->SetFont(TextFont);
}

void ULabel::SetText(const FText& NewText)
{
	verify(TextWidget);
	TextWidget->SetText(NewText);
}
