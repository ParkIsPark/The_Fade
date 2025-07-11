// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"
#include "PlayerCharacter.generated.h"


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
	// 움직임
	void Move(const FInputActionValue& Value); // 움직임. 

	void ShowDesCursor(const FVector Destination); // 움직이는 방향으로 커서 생성.
	void HideDesCursor(const FVector Destination); // 커서 다시 숨기기

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
private:
	/** 카메라 Arm(오브젝트와 충돌시 카메라 위치 조정) 변수, Private지만 블루프린트에서 access 가능(AllowPrivateAccess). */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** 캐릭터 따라오는 카메라 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	/** 플레이어 input -> Action 매핑되어 있는 EnhencedInput 매핑*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/*플레이어 액션 관련 Action 콘텐츠들*/

	//우클릭 -> 움직임
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	

};
