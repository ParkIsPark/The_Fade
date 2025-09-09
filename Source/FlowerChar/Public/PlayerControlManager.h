// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ApporachInteractTrigger.h"

#include "PlayerControlManager.generated.h"

/**
 * 
 */
UCLASS()
class FLOWERCHAR_API APlayerControlManager : public APlayerController
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	APlayerControlManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// Ŭ�� ��ǥ ������
	bool GetClickVector(FVector& OutLocation);

	// ���콺 ��ġ �Ʒ��� ������Ʈ Ÿ�� Ȯ��
	AActor* GetMouseCursorUnderActor();

	

	// ��ȣ�ۿ� ������ ������Ʈ���� Ȯ��
	void IsInteractableActor();
	AApporachInteractTrigger* PreviousApproachTriggerActor;//������ ������ ������Ʈ



};
