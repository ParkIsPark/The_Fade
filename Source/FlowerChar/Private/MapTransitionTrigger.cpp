// Fill out your copyright notice in the Description page of Project Settings.


#include "MapTransitionTrigger.h"
#include "CinematicManager.h"

AMapTransitionTrigger::AMapTransitionTrigger()
{
}


void AMapTransitionTrigger::OnInteract()
{
	CinematicManager->Bindfunc0.BindUObject(this, &AMapTransitionTrigger::MoveToNextMap); // ���ε� 
	CinematicManager->FadeInOut();

}

void AMapTransitionTrigger::MoveToNextMap()
{
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	PlayerCharacter->SetActorLocation(NewMapPoint);
	MainCameraManager->ChangeMainCamera(NewCameraIndex);
	if (CinematicManager->Bindfunc0.IsBound()) {
		// ���� ���ε��Ǿ� �ִٸ� -> 1�� ��� �ڵ�
		CinematicManager->Bindfunc0.Unbind(); // ����ε� 

	}
}




