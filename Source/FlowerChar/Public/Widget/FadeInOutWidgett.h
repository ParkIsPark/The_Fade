// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FadeInOutWidgett.generated.h"

/**
 * 
 */
UCLASS()
class FLOWERCHAR_API UFadeInOutWidgett : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	class UBorder* Border_Fade; // 이름 똑같이 맞춰줌

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* FadeIn; // 동일

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* FadeOut; // 동일

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* FadeInOut; // 동일

	UFUNCTION()
	void PlayFadeIn();

	UFUNCTION()
	void PlayFadeOut();
};
