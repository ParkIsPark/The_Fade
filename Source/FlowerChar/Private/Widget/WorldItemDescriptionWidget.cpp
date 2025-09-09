// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/WorldItemDescriptionWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"

void UWorldItemDescriptionWidget::SetTitleText(FText text)
{
	Title->SetText(text);
}

void UWorldItemDescriptionWidget::SetContentsText(FText text)
{
	Contents->SetText(text);
}

void UWorldItemDescriptionWidget::ExitThisWindow()
{
	this->RemoveFromParent();
}

void UWorldItemDescriptionWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (ExitButton) {
		ExitButton->OnClicked.AddDynamic(this, &UWorldItemDescriptionWidget::ExitThisWindow);
	}
}
