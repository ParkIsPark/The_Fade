// Fill out your copyright notice in the Description page of Project Settings.


#include "CinematicManager.h"
#include "Animation/WidgetAnimation.h" 
#include "PlayerControlManager.h"
#include "MapTransitionTrigger.h"
#include "Widget/FadeInOutWidgett.h"

// Sets default values
ACinematicManager::ACinematicManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACinematicManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACinematicManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ACinematicManager::FadeIn() 
{
	APlayerControlManager* Controller = Cast<APlayerControlManager>(GetWorld()->GetFirstPlayerController());
	if (Controller != nullptr) {
		if (fadeWidgetInstance)
		{
			fadeWidgetInstance->AddToViewport();
			FWidgetAnimationDynamicEvent endEvent; // ���ε����� �� �̺�Ʈ
			endEvent.BindDynamic(this, &ACinematicManager::RemoveFadeOutWidget);
			fadeWidgetInstance->BindToAnimationFinished(fadeWidgetInstance->FadeIn, endEvent);
			fadeWidgetInstance->PlayFadeIn();
			
		}
		
	}
}

// 
void ACinematicManager::FadeOut()
{
	RemoveFadeOutWidget();
	APlayerControlManager* Controller = Cast<APlayerControlManager>(GetWorld()->GetFirstPlayerController());
	if (Controller != nullptr) {
		fadeWidgetInstance = Cast<UFadeInOutWidgett>(CreateWidget(GetWorld(), FadeWidget));
		if (fadeWidgetInstance)
		{
			fadeWidgetInstance->AddToViewport();

			FWidgetAnimationDynamicEvent endEvent; // ���ε����� �� �̺�Ʈ
			endEvent.BindDynamic(this, &ACinematicManager::RemoveFadeOutWidget);
			fadeWidgetInstance->BindToAnimationFinished(fadeWidgetInstance->FadeOut, endEvent);
			fadeWidgetInstance->PlayFadeOut();
		}

	}
}

void ACinematicManager::FadeInOut()
{
	RemoveFadeOutWidget(); // Ȥ�� �� ������ ������Ʈ ����ؼ� ���� �۾�.
	//���̵� �� �ƿ�
	APlayerControlManager* Controller = Cast<APlayerControlManager>(GetWorld()->GetFirstPlayerController());
	if (Controller != nullptr) {
		fadeWidgetInstance = Cast<UFadeInOutWidgett>(CreateWidget(GetWorld(), FadeWidget));
		if (fadeWidgetInstance)
		{
			fadeWidgetInstance->AddToViewport();
	
			FWidgetAnimationDynamicEvent endEvent1; // ���ε����� �� �̺�Ʈ 1
			endEvent1.BindDynamic(this, &ACinematicManager::OnCinematicEndThen);
			AndOnCinematicEndMordFunc = [this]() {
				if (fadeWidgetInstance != nullptr) {
					fadeWidgetInstance->PlayFadeIn(); // ���̵� �� �ٿ��. 
				}
			};
			FWidgetAnimationDynamicEvent endEvent2; // ���ε����� �� �̺�Ʈ 2
			endEvent2.BindDynamic(this, &ACinematicManager::RemoveFadeOutWidget);
			fadeWidgetInstance->BindToAnimationFinished(fadeWidgetInstance->FadeOut, endEvent1); // �� �̵� ���ε�
			fadeWidgetInstance->BindToAnimationFinished(fadeWidgetInstance->FadeIn, endEvent2); // �ٽ� ��Ÿ���� ���� ���� ���ε�

			
			fadeWidgetInstance->PlayFadeOut(); // ��ο�����
		}

	}
}

void ACinematicManager::RemoveFadeOutWidget()
{
	if (fadeWidgetInstance) {
		fadeWidgetInstance->RemoveFromParent(); // ����
		fadeWidgetInstance = nullptr;
	}
}

void ACinematicManager::OnCinematicEndThen()
{
	Bindfunc0.Execute();
	if (AndOnCinematicEndMordFunc != nullptr) {
		AndOnCinematicEndMordFunc(); // ����
		AndOnCinematicEndMordFunc = nullptr; // �ʱ�ȭ �۾�.
	}
}