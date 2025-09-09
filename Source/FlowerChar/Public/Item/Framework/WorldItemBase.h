// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ApporachInteractTrigger.h"
#include "WorldItemBase.generated.h"

/**
 * 
 */
UCLASS()
class FLOWERCHAR_API AWorldItemBase : public AApporachInteractTrigger
{
	GENERATED_BODY()
public:
	AWorldItemBase();


public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	class UInteractionComponent* InteractionCompInst;


public:
	//=======================================
	// 오버라이드 섹션
	//==========================================

	virtual void OnInteract() override;

};
