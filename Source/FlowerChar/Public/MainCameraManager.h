// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraMovementStruct.h" // ī�޶� ������ ��Ʈ��Ʈ
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

	// ī�޶� �����̴� �޼���
	void MoveCamera(FVector mv, float speed);

	//ī�޶� ��ġ ������ �Լ�
	FVector GetCameraLocation();
	FVector GetCameraArmLocation(); // ī�޶� �����̴� ������Ʈ ��ġ �������� �Լ�. 

	void SetCameraArmLocation(FVector CameraArmTarget); // ī�޶� �� ������


	//�������� : ī�޶� �ٲٴ� �Լ� �����


	//��뿩�� ��Ȯ���� �޼����
	void LetCameraMove(FCameraMovement mv);

	void AddCameraMv(FCameraMovement mv); // ī�޶� ������ �߰�



public:
	UPROPERTY(EditAnywhere, Category = "Camera")

	TArray<AActor*> MainCamera; // ���� ī�޶� ���� ��
	UPROPERTY(EditAnywhere, Category = "Camera")
	TArray<AActor*> CameraArm; // ī�޶� ȸ�� �����ϴ� ���� ���� ��.

	int32 CurrentCameraIndex;//���� ī�޶� �ε���

	void SetCameraIndex(int32 index); // ī�޶� �ε��� ��ü, ������ ó�� ������ �� �̰ɷ�
	void ChangeMainCamera(int32 index); // ī�޶� ��ü. 

	
	UPROPERTY(EditAnywhere, Category = "Vector")
	FVector2D Bound1;// �ִ� ��ġ 1
	UPROPERTY(EditAnywhere, Category = "Vector")
	FVector2D Bound2;//�ִ� ��ġ



	//�������� 2 : ���� ����.
	UPROPERTY(EditAnywhere)
	TArray<FCameraMovement> CameraMv; // ī�޶� ������ ����

	// ��ũ������ ������(visible only)
	UPROPERTY(VisibleAnywhere)
	bool isMoving;//ī�޶� �����̰� �ִ°�?

	UPROPERTY(VisibleAnywhere)
	FVector TargetLocation; // ī�޶� �����̰� �ִ� ��� ��ġ

	UPROPERTY(VisibleAnywhere)
	FRotator TargetRotate;

	FVector StartLocation; // ī�޶� ����� ��ġ


};
