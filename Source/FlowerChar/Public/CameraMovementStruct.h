// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraMovementStruct.generated.h"

UCLASS()
class FLOWERCHAR_API ACameraMovementStruct : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACameraMovementStruct();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
};
// Atomic : ����ȭ�Ǿ� ����(������ ���� ����) / �������Ʈ ���� ���� Ÿ��. 
USTRUCT(Atomic, BlueprintType)

struct FCameraMovement
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Position")
	FVector value; // �̵��ϴ� ��ǥ��

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Position")
	float speed; // �ӵ�
	 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotate")
	FRotator rotate; // (ȸ���� ���� ��) ȸ���ϴ� ��

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotate")
	float RotateSpeed; // ȸ���ϴ� �ӵ�
	
	


	
};
