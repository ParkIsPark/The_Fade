// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TFTrigger.h"
#include "Components/BoxComponent.h" // �ڽ� ������Ʈ �߰���
#include "Components/WidgetComponent.h" // ���� �߰���
#include "ApporachInteractTrigger.generated.h"

/**
 * 
 */
UCLASS(Abstract)
 class FLOWERCHAR_API AApporachInteractTrigger : public ATFTrigger
{
	GENERATED_BODY()

public:
	//������

	AApporachInteractTrigger();


public:

	
	//====================================================================================
	// ���� (Settings)
	//====================================================================================

	UPROPERTY(Category = "Setting", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bShowKeyNoticeWidget; // Ű�� �˷��ִ� ������ �����ұ��?
	
	//====================================================================================
	// �ݸ��� ���� (Collision Settings)
	//====================================================================================

	UPROPERTY(Category = Collision, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* BoxCollider;  // �浹 �����ϴ� �ڽ� �ݶ��̴�

	UPROPERTY(Category = Collision, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FVector ColliderBoxSize; // �ݶ��̴� �ڽ� ������, �����ڿ��� �ʱ�ȭ�ϱ� ����.
	

	



	//====================================================================================
	// UI ���� (UI Settings)
	//====================================================================================
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "UI")
	UWidgetComponent* KeyNoticeWidget; // ��ȣ�ۿ��ϴ� Ű �˷��ִ� ����. 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "UI")
	TSubclassOf<UUserWidget> KeyNoticeWidgetClass; // ���� ���� Ŭ����

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "UI")
	FVector KeyNoticeWidgetVector; // ��ġ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "UI")
	FVector2D KeyNoticeWidgetSize; // ������


	//====================================================================================
	// ���� ���� ���� (Internal State)
	//====================================================================================

	UPROPERTY(Category = Player, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	APlayerCharacter* Player; // �÷��̾� 

	bool IsUnderMouse = false; // ���콺 �Ʒ��� �ֳ���?

	
	//Ʈ���� �߻� �� ȣ��Ǵ� �޼����
	UFUNCTION()
	virtual void TriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult); // �������� ���۵��� ��

	//OverlappedComponent: �̺�Ʈ�� �߻���Ų ������Ʈ(���� ��ü�� ������Ʈ).
	//OtherActor : �浹�� �ٸ� ����.
	//OtherComp : OtherActor������ �浹�� ������Ʈ.
	//OtherBodyIndex : �浹�� �ٸ� ������ ��ü �ε���(��ü�� ���� ���� ���).
	//bFromSweep : ������Ʈ �浹 ����(�浹�� ������Ʈ�� �����ߴ��� ����).
	//SweepResult : �浹 ������ �����ϴ� FHitResult ����ü.

	UFUNCTION()
	virtual void TriggerEndOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	//���� �Ϸ�� �Լ�
	void ShowKeyNoticeWidget(); // Ű �˷��ִ� ������ �巯��
	void HideKeyNoticeWidget(); // Ű �˷��ִ� ������ Hide��



	// TFTrigger���� Override�ϴ� �Լ���. �ӽ� ����
	// �ڼյ鿡�� ���⸦ �����ؼ� Ʈ���� �ý��� �ϼ��ϸ� ��. 
	virtual void OnPlayerTrigger() override; // �ӽ� ����
	virtual void OnPlayerTriggerEnd() override; // �ӽ� ����

	virtual void OnInteract(); // PlayerCharacter���� �޾Ƽ� �۵���ų �Լ�. 

	//�⺻ �Լ�
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
};
