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

class AApporachInteractTrigger; // ��ȯ ����


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
	
	//��Ŭ�� -> �÷��̾� �̵�.
	void Move(const FInputActionValue& Value); // ������. 
	void ShowDesCursor(const FVector Destination); // �����̴� �������� Ŀ�� ����.
	void HideDesCursor(const FVector Destination); // Ŀ�� �ٽ� �����
	void IsArrive(); // ������ �������� Ȯ��

	//�̵�Ŭ���巡�� -> ī�޶� ������.
	void CameraMoveStart(const FInputActionValue& Value);
	void CameraMove(const FInputActionValue& Value);
	void CameraMoveFinish(const FInputActionValue& Value);
	
	//EŬ�� -> ��ȣ�ۿ�

	void InteractObj(const FInputActionValue& Value);
	void isInteractable(); // ��ȣ�ۿ� ������ �������� Ȯ��. 

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
private:

	/** Action ���εǾ� �ִ� EnhencedInput �������� ����*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/// Manager��

	//������Ʈ�Ŵ���
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Manager, meta = (AllowPrivateAccess = "true"))
	AObjectManager* ObjectManager;

	//ī�޶� �Ŵ���
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Manager, meta = (AllowPrivateAccess = "true"))
	AMainCameraManager* MainCameraManager;


	/*�÷��̾� ���� ���� ������*/

	//��Ŭ�� -> ������
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	//Ŀ�� �Ž�
	AStaticMeshActor* Cursor;

	//�÷��̾��� �̵� ������.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = RealPlay, meta = (AllowPrivateAccess = "true"))
	FVector Dest;
	
	//�̵� ���ΰ�?
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = RealPlay, meta = (AllowPrivateAccess = "true"))
	bool isMoving = false;



	//�̵� �� Ŭ�� -> ī�޶� ������
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* CameraMoveAction;


	FVector2D ClickVector; //�巡�׿� -> ���� Ŭ���� ��ġ
	FVector2D PostClickVector;//�巡�׿� -> ������ Ŭ���� ��ġ
	bool isDrag = false; // �巡�� ���ΰ�?


	
	//��Ŭ�� -> ī�޶� rotation ����. 
	
public:
	//E Ŭ�� -> ��ȣ�ۿ�
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	void MoveToInteractTarget(); // ����� �̵�.
	AApporachInteractTrigger* InteractTarget; // ��ȣ�ۿ� ���� ������Ʈ�� �� �ʿ� ��. 
	bool bMovingToInteractActor = false; // ������Ʈ ������ �̵��ϰ� �ִ°�?

	TFunction<void()> InteractFunc;//�Լ� ������, ���߿� TFTrigger�ʿ��� �������ִ� �ݹ� �Լ��� ���� �ٲ�. 
	bool isTriggered; // ���� Ʈ���Ű� ������ �������� Ȯ��
	


	

	
	
};
