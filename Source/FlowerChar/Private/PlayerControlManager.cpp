// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControlManager.h"


APlayerControlManager::APlayerControlManager()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	bEnableStreamingSource = true; //���� ��Ʈ���ֿ� �ҽ� ��� ���. 

	//��ȣ�ۿ� ���� �ʱ�ȭ 
	PreviousApproachTriggerActor = nullptr;

}

// Called when the game starts or when spawned
void APlayerControlManager::BeginPlay()
{
	Super::BeginPlay();
	bShowMouseCursor = true;
	UE_LOG(LogTemp, Log, TEXT("[PlayerControlManager] Mouse Cursor On"));

}

// ��Ŭ���� ��ǥ�� ��ǥ�� ���������� ����, ������ true, �ƴϸ� false
bool APlayerControlManager::GetClickVector(FVector& OutLocation)
{
	UE_LOG(LogTemp, Log, TEXT("[PlayerControlManager] Get Click Vector"));
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit); // �������� �浹�� �ִٸ� �ϳ��� ����
	if (Hit.bBlockingHit) {
		OutLocation = Hit.ImpactPoint;
		return true;
	}
	return false;
}

AActor* APlayerControlManager::GetMouseCursorUnderActor()
{
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit); // �� �� ������ ����. 
	if (Hit.bBlockingHit) // ���� �浹������
	{

		// ���� ������
		UPrimitiveComponent* HitComponent = Hit.GetComponent(); // ������Ʈ
		AActor* HitActor = HitComponent->GetOwner();
		if (HitActor)
		{
		
			return HitActor;
		}
	

		
	}


	return nullptr; // �ƹ��͵� ������
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

		//���� ������ Ŭ���� ������Ʈ�� �� �̻� ���� ��
		PreviousApproachTriggerActor->IsUnderMouse = false;
		if (!Cast<APlayerCharacter>(GetPawn())->bMovingToInteractActor) {
			Cast<APlayerCharacter>(GetPawn())->InteractTarget = nullptr;
			//�̵� ���� �ƴ϶�� �����
		}
	}

}

// Called every frame
void APlayerControlManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//�Ʒ��� ��ȣ�ۿ� ������ ���� �մ��� Ȯ��
	IsInteractableActor();
	
	
}
