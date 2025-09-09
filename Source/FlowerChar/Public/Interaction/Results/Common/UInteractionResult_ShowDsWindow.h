// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interaction/Framework/InteractionResultBase.h"
#include "UInteractionResult_ShowDsWindow.generated.h"

/**
 * 
 */
UCLASS()
class FLOWERCHAR_API UUInteractionResult_ShowDsWindow : public UInteractionResultBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting")
	FText Title;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting")
	FText Contents;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setting")
	TSubclassOf<class UWorldItemDescriptionWidget> DescriptionWidget;
	class UWorldItemDescriptionWidget* DescriptionWidgetInstance;

	bool bShowingWindow = false;

	virtual void Execute(APlayerCharacter* Player) override;

	
	
};
