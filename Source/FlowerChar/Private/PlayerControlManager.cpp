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

// 우클릭한 좌표의 좌표값 참조값으로 리턴, 성공시 true, 아니면 false
bool APlayerControlManager::GetRightClickVector(FVector& OutLocation)
{
	UE_LOG(LogTemp, Log, TEXT("[PlayerControlManager] Right Click"));
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit); // 여러개의 충돌이 있다면 하나만 검출
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
