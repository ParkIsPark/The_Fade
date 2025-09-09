// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControlManager.h"


APlayerControlManager::APlayerControlManager()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	bEnableStreamingSource = true; //레벨 스트리밍용 소스 사용 허용. 

	//상호작용 관련 초기화 
	PreviousApproachTriggerActor = nullptr;

}

// Called when the game starts or when spawned
void APlayerControlManager::BeginPlay()
{
	Super::BeginPlay();
	bShowMouseCursor = true;
	UE_LOG(LogTemp, Log, TEXT("[PlayerControlManager] Mouse Cursor On"));

}

// 우클릭한 좌표의 좌표값 참조값으로 리턴, 성공시 true, 아니면 false
bool APlayerControlManager::GetClickVector(FVector& OutLocation)
{
	UE_LOG(LogTemp, Log, TEXT("[PlayerControlManager] Get Click Vector"));
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit); // 여러개의 충돌이 있다면 하나만 검출
	if (Hit.bBlockingHit) {
		OutLocation = Hit.ImpactPoint;
		return true;
	}
	return false;
}

AActor* APlayerControlManager::GetMouseCursorUnderActor()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit); // 좀 더 정밀한 개발. 
	if (Hit.bBlockingHit) // 만약 충돌됐으면
	{

		// 액터 얻어오기
		UPrimitiveComponent* HitComponent = Hit.GetComponent(); // 컴포넌트
		AActor* HitActor = HitComponent->GetOwner();
		if (HitActor)
		{
		
			return HitActor;
		}
	

		
	}


	return nullptr; // 아무것도 없으면
}

void APlayerControlManager::IsInteractableActor()
{
	AActor* HitActor = GetMouseCursorUnderActor();
	AApporachInteractTrigger* ApproachTriggerActor;
	if ((ApproachTriggerActor = Cast<AApporachInteractTrigger>(HitActor)) != nullptr) {
		ApproachTriggerActor->IsUnderMouse = true;
		PreviousApproachTriggerActor = ApproachTriggerActor;

		Cast<APlayerCharacter>(GetPawn())->InteractTarget = ApproachTriggerActor;
		
		
	}
	if (PreviousApproachTriggerActor != nullptr &&
		ApproachTriggerActor != PreviousApproachTriggerActor) {

		//만약 이전에 클릭한 오브젝트가 더 이상 없을 때
		PreviousApproachTriggerActor->IsUnderMouse = false;
		if (!Cast<APlayerCharacter>(GetPawn())->bMovingToInteractActor) {
			Cast<APlayerCharacter>(GetPawn())->InteractTarget = nullptr;
			//이동 중이 아니라면 비워있
		}
	}

}

// Called every frame
void APlayerControlManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//아래에 상호작용 가능한 액터 잇는지 확인
	IsInteractableActor();
	
	
}
