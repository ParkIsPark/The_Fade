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
			FWidgetAnimationDynamicEvent endEvent; // 바인드해줄 끝 이벤트
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

			FWidgetAnimationDynamicEvent endEvent; // 바인드해줄 끝 이벤트
			endEvent.BindDynamic(this, &ACinematicManager::RemoveFadeOutWidget);
			fadeWidgetInstance->BindToAnimationFinished(fadeWidgetInstance->FadeOut, endEvent);
			fadeWidgetInstance->PlayFadeOut();
		}

	}
}

void ACinematicManager::FadeInOut()
{
	RemoveFadeOutWidget(); // 혹시 모를 생성된 오브젝트 대비해서 제거 작업.
	//페이드 인 아웃
	APlayerControlManager* Controller = Cast<APlayerControlManager>(GetWorld()->GetFirstPlayerController());
	if (Controller != nullptr) {
		fadeWidgetInstance = Cast<UFadeInOutWidgett>(CreateWidget(GetWorld(), FadeWidget));
		if (fadeWidgetInstance)
		{
			fadeWidgetInstance->AddToViewport();
	
			FWidgetAnimationDynamicEvent endEvent1; // 바인드해줄 끝 이벤트 1
			endEvent1.BindDynamic(this, &ACinematicManager::OnCinematicEndThen);
			AndOnCinematicEndMordFunc = [this]() {
				if (fadeWidgetInstance != nullptr) {
					fadeWidgetInstance->PlayFadeIn(); // 페이드 인 바운드. 
				}
			};
			FWidgetAnimationDynamicEvent endEvent2; // 바인드해줄 끝 이벤트 2
			endEvent2.BindDynamic(this, &ACinematicManager::RemoveFadeOutWidget);
			fadeWidgetInstance->BindToAnimationFinished(fadeWidgetInstance->FadeOut, endEvent1); // 맵 이동 바인딩
			fadeWidgetInstance->BindToAnimationFinished(fadeWidgetInstance->FadeIn, endEvent2); // 다시 나타나며 유닛 삭제 바인딩

			
			fadeWidgetInstance->PlayFadeOut(); // 어두워지고
		}

	}
}

void ACinematicManager::RemoveFadeOutWidget()
{
	if (fadeWidgetInstance) {
		fadeWidgetInstance->RemoveFromParent(); // 제거
		fadeWidgetInstance = nullptr;
	}
}

void ACinematicManager::OnCinematicEndThen()
{
	Bindfunc0.Execute();
	if (AndOnCinematicEndMordFunc != nullptr) {
		AndOnCinematicEndMordFunc(); // 실행
		AndOnCinematicEndMordFunc = nullptr; // 초기화 작업.
	}
}