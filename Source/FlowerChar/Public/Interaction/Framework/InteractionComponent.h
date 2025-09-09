// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interaction/Framework/InteractionConditionBase.h"
#include "Interaction/Framework/InteractionResultBase.h"
#include "PlayerCharacter.h"
#include "InteractionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FLOWERCHAR_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	/** ��ȣ�ۿ��� ���� �� �ϳ��� �����Դϴ�. */
	UPROPERTY(EditAnywhere, Instanced, Category = "Interaction")
	UInteractionConditionBase* Condition;

	/** ���� ���� �� ������� ����� ������� ����Դϴ�. */
	UPROPERTY(EditAnywhere, Instanced, Category = "Interaction")
	TArray<UInteractionResultBase*> Results;
public:	
	// Sets default values for this component's properties
	UInteractionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	/// <summary>
	/// ��ȣ�ۿ� �õ�. 
	/// </summary>
	void AttemptInteraction(APlayerCharacter* Player);
};
