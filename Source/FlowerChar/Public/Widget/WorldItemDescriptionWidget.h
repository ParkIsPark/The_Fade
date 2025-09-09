// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WorldItemDescriptionWidget.generated.h"

/**
 * 
 */
UCLASS()
class FLOWERCHAR_API UWorldItemDescriptionWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(meta = (BindWidget))
	class UCanvasPanel* Canvas;
	UPROPERTY(meta = (BindWidget))
	class UBorder* Border;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Title;
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Contents;
	UPROPERTY(meta = (BindWidget))
	class UButton* ExitButton;
	UFUNCTION()
	void SetTitleText(FText text);

	UFUNCTION()
	void SetContentsText(FText text);

	UFUNCTION()
	void ExitThisWindow();

	UFUNCTION()
	virtual void NativeConstruct() override;

	
};
