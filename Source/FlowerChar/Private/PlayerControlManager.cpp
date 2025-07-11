// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerControlManager.h"

APlayerControlManager::APlayerControlManager()
{
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerControlManager::BeginPlay()
{
	Super::BeginPlay();
	bShowMouseCursor = true;
	UE_LOG(LogTemp, Log, TEXT("[PlayerControlManager] Mouse Cursor On"));

}

// ��Ŭ���� ��ǥ�� ��ǥ�� ���������� ����, ������ true, �ƴϸ� false
bool APlayerControlManager::GetRightClickVector(FVector& OutLocation)
{
	UE_LOG(LogTemp, Log, TEXT("[PlayerControlManager] Right Click"));
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit); // �������� �浹�� �ִٸ� �ϳ��� ����
	if (Hit.bBlockingHit) {
		OutLocation = Hit.ImpactPoint;
		return true;
	}
	return false;
}

// Called every frame
void APlayerControlManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}
