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

	//�� �̵� ���� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Map, meta = (AllowPrivateAccess = "true"))
	FVector NewMapPoint; // �̵� ��ǥ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Map, meta = (AllowPrivateAccess = "true"))
	int32 NewCameraIndex; // ���� �ٲ�� ī�޶�


	// Manager
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Manager, meta = (AllowPrivateAccess = "true"))
	AMainCameraManager* MainCameraManager;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Manager, meta = (AllowPrivateAccess = "true"))
	class ACinematicManager* CinematicManager;

	//���� �Լ�
	void MoveToNextMap();
	
	void OnInteract() override;
};
