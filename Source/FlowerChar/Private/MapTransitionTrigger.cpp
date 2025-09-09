// Fill out your copyright notice in the Description page of Project Settings.


#include "MapTransitionTrigger.h"
#include "CinematicManager.h"

AMapTransitionTrigger::AMapTransitionTrigger()
{
}


void AMapTransitionTrigger::OnInteract()
{
	CinematicManager->Bindfunc0.BindUObject(this, &AMapTransitionTrigger::MoveToNextMap); // 바인드 
	CinematicManager->FadeInOut();

}

void AMapTransitionTrigger::MoveToNextMap()
{
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	PlayerCharacter->SetActorLocation(NewMapPoint);
	MainCameraManager->ChangeMainCamera(NewCameraIndex);
	if (CinematicManager->Bindfunc0.IsBound()) {
		// 만약 바인딩되어 있다면 -> 1차 방어 코드
		CinematicManager->Bindfunc0.Unbind(); // 언바인드 

	}
}




