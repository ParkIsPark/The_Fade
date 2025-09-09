// Fill out your copyright notice in the Description page of Project Settings.

#include "ObjectManager.h"

// Sets default values
AObjectManager::AObjectManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	PutCommonMesh();

	if (PollingObjectPath.Num() > 0) {

		PutPollingMesh();
	}
	if (NonPollingObjectPath.Num() > 0) {
		PutNonPollingMesh();
	}

}

// Called when the game starts or when spawned
void AObjectManager::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void AObjectManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AObjectManager::PutCommonMesh()
{
	//기본적으로 사용되는 오브젝트들 
	
	//1. 커서
	static ConstructorHelpers::FObjectFinder<UStaticMesh>Cursor(TEXT("/Game/Asset/Common/UI/HUD/PointCircle_mesh"));
	if (Cursor.Succeeded()) {
		CommonObject.Emplace(TEXT("Cursor"), Cursor.Object); // 생성자로 input
	}
	

}

void AObjectManager::PutPollingMesh()
{
	//현재는 필요없어서 미구현
}

void AObjectManager::PutNonPollingMesh()
{
	//현재는 필요없어서 미구현
}

UStaticMesh* AObjectManager::GetCommonMesh(FString name)
{
	if (CommonObject.Contains(name))
	{
		return CommonObject[name];
	}
	else {
		return nullptr;
	}
}

UStaticMesh* AObjectManager::GetPollingMesh(FString name)
{
	return nullptr;
}

UStaticMesh* AObjectManager::GetNonPollingMesh(FString name)
{
	return nullptr;
}


