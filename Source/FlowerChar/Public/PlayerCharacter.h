// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"

#include "ObjectManager.h"
#include "MainCameraManager.h"
#include "EngineUtils.h"
#include "Engine/StaticMeshActor.h"

#include "PlayerCharacter.generated.h"

class AApporachInteractTrigger; // 순환 참조


UCLASS()
class FLOWERCHAR_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

	

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	
	//좌클릭 -> 플레이어 이동.
	void Move(const FInputActionValue& Value); // 움직임. 
	void ShowDesCursor(const FVector Destination); // 움직이는 방향으로 커서 생성.
	void HideDesCursor(const FVector Destination); // 커서 다시 숨기기
	void IsArrive(); // 도착한 상태인지 확인

	//미들클릭드래그 -> 카메라 움직임.
	void CameraMoveStart(const FInputActionValue& Value);
	void CameraMove(const FInputActionValue& Value);
	void CameraMoveFinish(const FInputActionValue& Value);
	
	//E클릭 -> 상호작용

	void InteractObj(const FInputActionValue& Value);
	void isInteractable(); // 상호작용 가능한 상태인지 확인. 

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
private:

	/** Action 매핑되어 있는 EnhencedInput 가져오는 변수*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/// Manager들

	//오브젝트매니저
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Manager, meta = (AllowPrivateAccess = "true"))
	AObjectManager* ObjectManager;

	//카메라 매니저
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Manager, meta = (AllowPrivateAccess = "true"))
	AMainCameraManager* MainCameraManager;


	/*플레이어 조작 관련 변수들*/

	//좌클릭 -> 움직임
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	//커서 매시
	AStaticMeshActor* Cursor;

	//플레이어의 이동 목적지.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = RealPlay, meta = (AllowPrivateAccess = "true"))
	FVector Dest;
	
	//이동 중인가?
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = RealPlay, meta = (AllowPrivateAccess = "true"))
	bool isMoving = false;



	//미들 휠 클릭 -> 카메라 움직임
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* CameraMoveAction;


	FVector2D ClickVector; //드래그용 -> 지금 클릭한 위치
	FVector2D PostClickVector;//드래그용 -> 이전에 클릭한 위치
	bool isDrag = false; // 드래그 중인가?


	
	//우클릭 -> 카메라 rotation 조절. 
	
public:
	//E 클릭 -> 상호작용
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	void MoveToInteractTarget(); // 여기로 이동.
	AApporachInteractTrigger* InteractTarget; // 상호작용 들어온 오브젝트가 이 쪽에 들어감. 
	bool bMovingToInteractActor = false; // 오브젝트 쪽으로 이동하고 있는가?

	TFunction<void()> InteractFunc;//함수 포인터, 나중에 TFTrigger쪽에서 리턴해주는 콜백 함수에 의해 바뀜. 
	bool isTriggered; // 지금 트리거가 가능한 상태인지 확인
	


	

	
	
};
