// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/FadeInOutWidgett.h"

void UFadeInOutWidgett::PlayFadeIn()
{
	PlayAnimation(FadeIn);
	UE_LOG(LogTemp, Log, TEXT("FadeIn"));
}

void UFadeInOutWidgett::PlayFadeOut()
{
	PlayAnimation(FadeOut);
	UE_LOG(LogTemp, Log, TEXT("FadeOut"));
}
