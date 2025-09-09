// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraMovementStruct.h" // 카메라 움직임 스트럭트
#include "MainCameraManager.generated.h"

UCLASS()
class FLOWERCHAR_API AMainCameraManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMainCameraManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:

	// 카메라를 움직이는 메서드
	void MoveCamera(FVector mv, float speed);

	//카메라 위치 얻어오는 함수
	FVector GetCameraLocation();
	FVector GetCameraArmLocation(); // 카메라 움직이는 오브젝트 위치 가져오는 함수. 

	void SetCameraArmLocation(FVector CameraArmTarget); // 카메라 암 움직임


	//수정사항 : 카메라 바꾸는 함수 만들기


	//사용여부 불확실한 메서드들
	void LetCameraMove(FCameraMovement mv);

	void AddCameraMv(FCameraMovement mv); // 카메라 움직임 추가



public:
	UPROPERTY(EditAnywhere, Category = "Camera")

	TArray<AActor*> MainCamera; // 메인 카메라가 들어가는 곳
	UPROPERTY(EditAnywhere, Category = "Camera")
	TArray<AActor*> CameraArm; // 카메라 회전 결정하는 놈이 들어가는 곳.

	int32 CurrentCameraIndex;//현재 카메라 인덱스

	void SetCameraIndex(int32 index); // 카메라 인덱스 교체, 게임을 처음 시작할 땐 이걸로
	void ChangeMainCamera(int32 index); // 카메라 교체. 

	
	UPROPERTY(EditAnywhere, Category = "Vector")
	FVector2D Bound1;// 최대 위치 1
	UPROPERTY(EditAnywhere, Category = "Vector")
	FVector2D Bound2;//최대 위치



	//수정사항 2 : 여기 삭제.
	UPROPERTY(EditAnywhere)
	TArray<FCameraMovement> CameraMv; // 카메라 움직임 조절

	// 테크니컬한 변수들(visible only)
	UPROPERTY(VisibleAnywhere)
	bool isMoving;//카메라가 움직이고 있는가?

	UPROPERTY(VisibleAnywhere)
	FVector TargetLocation; // 카메라가 움직이고 있는 대상 위치

	UPROPERTY(VisibleAnywhere)
	FRotator TargetRotate;

	FVector StartLocation; // 카메라가 출발한 위치


};
