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
	// 클릭 좌표 얻어오기
	bool GetClickVector(FVector& OutLocation);

	// 마우스 위치 아래에 오브젝트 타입 확인
	AActor* GetMouseCursorUnderActor();

	

	// 상호작용 가능한 오브젝트인지 확인
	void IsInteractableActor();
	AApporachInteractTrigger* PreviousApproachTriggerActor;//이전에 감지한 오브젝트



};
