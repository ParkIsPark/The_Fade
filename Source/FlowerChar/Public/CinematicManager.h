// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Blueprint/UserWidget.h"
#include "CinematicManager.generated.h"


DECLARE_DELEGATE(FCineMaticThenFunc0);

UCLASS()
class FLOWERCHAR_API ACinematicManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACinematicManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
public:

	// 외부에서 함수 받아오는 델리게이트 패턴
	FCineMaticThenFunc0 Bindfunc0; // 인수 0개짜리
	UFUNCTION()
	void OnCinematicEndThen(); // 브릿지 함수
	TFunction<void()> AndOnCinematicEndMordFunc; // 브릿지 함수 다음에 실행될 함수 목록.

	//위젯에 들어가는 애들

	///페이드 인 - 아웃 위젯
	UPROPERTY(EditAnywhere, Category = "WidgetSource")
	TSubclassOf<class UFadeInOutWidgett> FadeWidget; // 페이드 인/아웃
	class UFadeInOutWidgett* fadeWidgetInstance; // 위젯 인스턴스

	UFUNCTION()
	void FadeIn(); // 페이드 인
	UFUNCTION() 
	void FadeOut(); // 페이드 아웃
	UFUNCTION()
	void FadeInOut(); // 페이드 인 아웃 한번에 처리
	UFUNCTION()
	void RemoveFadeOutWidget(); // 위젯 제거

	
	

	

};
