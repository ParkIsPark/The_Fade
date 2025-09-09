// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlayerCharacter.h"
#include "InteractionConditionBase.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable, EditInlineNew, DefaultToInstanced)
class FLOWERCHAR_API UInteractionConditionBase : public UObject
{
	GENERATED_BODY()
public:
	virtual bool IsMet(APlayerCharacter* Player) const { return true; }; // 조건 검사. 
	
};
