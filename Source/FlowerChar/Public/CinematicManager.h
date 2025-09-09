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

	// �ܺο��� �Լ� �޾ƿ��� ��������Ʈ ����
	FCineMaticThenFunc0 Bindfunc0; // �μ� 0��¥��
	UFUNCTION()
	void OnCinematicEndThen(); // �긴�� �Լ�
	TFunction<void()> AndOnCinematicEndMordFunc; // �긴�� �Լ� ������ ����� �Լ� ���.

	//������ ���� �ֵ�

	///���̵� �� - �ƿ� ����
	UPROPERTY(EditAnywhere, Category = "WidgetSource")
	TSubclassOf<class UFadeInOutWidgett> FadeWidget; // ���̵� ��/�ƿ�
	class UFadeInOutWidgett* fadeWidgetInstance; // ���� �ν��Ͻ�

	UFUNCTION()
	void FadeIn(); // ���̵� ��
	UFUNCTION() 
	void FadeOut(); // ���̵� �ƿ�
	UFUNCTION()
	void FadeInOut(); // ���̵� �� �ƿ� �ѹ��� ó��
	UFUNCTION()
	void RemoveFadeOutWidget(); // ���� ����

	
	

	

};
