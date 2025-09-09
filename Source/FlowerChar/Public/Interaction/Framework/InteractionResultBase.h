// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlayerCharacter.h"
#include "InteractionResultBase.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable, EditInlineNew, DefaultToInstanced)
class FLOWERCHAR_API UInteractionResultBase : public UObject
{
	GENERATED_BODY()
public:
	virtual void Execute(APlayerCharacter* Player) {};
	
};
