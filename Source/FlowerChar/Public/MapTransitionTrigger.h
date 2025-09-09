// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ApporachInteractTrigger.h"
#include "Kismet/GameplayStatics.h"
#include "MainCameraManager.h"
#include "MapTransitionTrigger.generated.h"

/**
 * 
 */
UCLASS()
class FLOWERCHAR_API AMapTransitionTrigger : public AApporachInteractTrigger
{
	GENERATED_BODY()

public:

	AMapTransitionTrigger();
public:

	//맵 이동 관련 정보
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Map, meta = (AllowPrivateAccess = "true"))
	FVector NewMapPoint; // 이동 좌표
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Map, meta = (AllowPrivateAccess = "true"))
	int32 NewCameraIndex; // 새로 바뀌는 카메라


	// Manager
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Manager, meta = (AllowPrivateAccess = "true"))
	AMainCameraManager* MainCameraManager;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Manager, meta = (AllowPrivateAccess = "true"))
	class ACinematicManager* CinematicManager;

	//고유 함수
	void MoveToNextMap();
	
	void OnInteract() override;
};
