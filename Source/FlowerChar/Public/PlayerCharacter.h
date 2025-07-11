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
	// ������
	void Move(const FInputActionValue& Value); // ������. 

	void ShowDesCursor(const FVector Destination); // �����̴� �������� Ŀ�� ����.
	void HideDesCursor(const FVector Destination); // Ŀ�� �ٽ� �����

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
private:
	/** ī�޶� Arm(������Ʈ�� �浹�� ī�޶� ��ġ ����) ����, Private���� �������Ʈ���� access ����(AllowPrivateAccess). */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** ĳ���� ������� ī�޶� */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	/** �÷��̾� input -> Action ���εǾ� �ִ� EnhencedInput ����*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/*�÷��̾� �׼� ���� Action ��������*/

	//��Ŭ�� -> ������
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	

};
