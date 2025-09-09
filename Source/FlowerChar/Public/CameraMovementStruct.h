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
// Atomic : 직렬화되어 저장(에디터 편집 가능) / 블루프린트 적용 가능 타입. 
USTRUCT(Atomic, BlueprintType)

struct FCameraMovement
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Position")
	FVector value; // 이동하는 좌표값

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Position")
	float speed; // 속도
	 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotate")
	FRotator rotate; // (회전이 있을 시) 회전하는 값

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rotate")
	float RotateSpeed; // 회전하는 속도
	
	


	
};
