// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
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
	// 우클릭 좌표 얻어오기
	bool GetRightClickVector(FVector& OutLocation);
};
