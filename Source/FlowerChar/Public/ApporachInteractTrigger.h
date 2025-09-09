// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TFTrigger.h"
#include "Components/BoxComponent.h" // 박스 컴포넌트 추가용
#include "Components/WidgetComponent.h" // 위젯 추가용
#include "ApporachInteractTrigger.generated.h"

/**
 * 
 */
UCLASS(Abstract)
 class FLOWERCHAR_API AApporachInteractTrigger : public ATFTrigger
{
	GENERATED_BODY()

public:
	//생성자

	AApporachInteractTrigger();


public:

	
	//====================================================================================
	// 설정 (Settings)
	//====================================================================================

	UPROPERTY(Category = "Setting", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bShowKeyNoticeWidget; // 키를 알려주는 위젯을 노출할까요?
	
	//====================================================================================
	// 콜리전 설정 (Collision Settings)
	//====================================================================================

	UPROPERTY(Category = Collision, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* BoxCollider;  // 충돌 감지하는 박스 콜라이더

	UPROPERTY(Category = Collision, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FVector ColliderBoxSize; // 콜라이더 박스 사이즈, 생성자에서 초기화하길 권장.
	

	



	//====================================================================================
	// UI 설정 (UI Settings)
	//====================================================================================
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "UI")
	UWidgetComponent* KeyNoticeWidget; // 상호작용하는 키 알려주는 위젯. 
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "UI")
	TSubclassOf<UUserWidget> KeyNoticeWidgetClass; // 위젯 들어가는 클래스

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "UI")
	FVector KeyNoticeWidgetVector; // 위치
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "UI")
	FVector2D KeyNoticeWidgetSize; // 사이즈


	//====================================================================================
	// 내부 상태 변수 (Internal State)
	//====================================================================================

	UPROPERTY(Category = Player, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	APlayerCharacter* Player; // 플레이어 

	bool IsUnderMouse = false; // 마우스 아래에 있나요?

	
	//트리거 발생 시 호출되는 메서드들
	UFUNCTION()
	virtual void TriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult); // 오버랩이 시작됐을 때

	//OverlappedComponent: 이벤트를 발생시킨 컴포넌트(현재 객체의 컴포넌트).
	//OtherActor : 충돌한 다른 액터.
	//OtherComp : OtherActor에서의 충돌한 컴포넌트.
	//OtherBodyIndex : 충돌한 다른 액터의 본체 인덱스(본체가 여러 개인 경우).
	//bFromSweep : 스위프트 충돌 여부(충돌을 스위프트로 검출했는지 여부).
	//SweepResult : 충돌 정보를 제공하는 FHitResult 구조체.

	UFUNCTION()
	virtual void TriggerEndOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	//구현 완료된 함수
	void ShowKeyNoticeWidget(); // 키 알려주는 위젯을 드러냄
	void HideKeyNoticeWidget(); // 키 알려주는 위젯을 Hide함



	// TFTrigger에서 Override하는 함수들. 임시 구현
	// 자손들에선 여기를 구현해서 트리거 시스템 완성하면 됨. 
	virtual void OnPlayerTrigger() override; // 임시 구현
	virtual void OnPlayerTriggerEnd() override; // 임시 구현

	virtual void OnInteract(); // PlayerCharacter에서 받아서 작동시킬 함수. 

	//기본 함수
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
};
