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
	class UBorder* Border_Fade; // �̸� �Ȱ��� ������

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* FadeIn; // ����

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* FadeOut; // ����

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	class UWidgetAnimation* FadeInOut; // ����

	UFUNCTION()
	void PlayFadeIn();

	UFUNCTION()
	void PlayFadeOut();
};
