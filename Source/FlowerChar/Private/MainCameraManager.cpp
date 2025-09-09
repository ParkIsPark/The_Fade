// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCameraManager.h"
#include "PlayerControlManager.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMainCameraManager::AMainCameraManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMainCameraManager::BeginPlay()
{
	Super::BeginPlay();

	CurrentCameraIndex = 0;
	//나중에 저장 기능 활성화하면 -> 플레이어 나오는 방향에서 인덱스 설저오디게 바꿀 것. 
	APlayerControlManager* controller = Cast<APlayerControlManager>(UGameplayStatics::GetPlayerController(this, 0));
	if (controller != nullptr) {
		controller->SetViewTarget(MainCamera[CurrentCameraIndex]);
	}
	
}

// Called every frame
void AMainCameraManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//카메라 바꾸기
void AMainCameraManager::SetCameraIndex(int32 index)
{
	CurrentCameraIndex = index;
}

void AMainCameraManager::ChangeMainCamera(int32 index)
{
	CurrentCameraIndex = index;

	//카메라 변경.
	APlayerControlManager* controller = Cast<APlayerControlManager>(UGameplayStatics::GetPlayerController(this, 0));
	if (controller != nullptr) {
		controller->SetViewTarget(MainCamera[CurrentCameraIndex]);
	}
}


//헬퍼 함수들
FVector AMainCameraManager::GetCameraLocation()
{
	return MainCamera[CurrentCameraIndex]->GetActorLocation();
}

FVector AMainCameraManager::GetCameraArmLocation()
{
	return CameraArm[CurrentCameraIndex]->GetActorLocation();
}


//카메라 위치 정하기. 
void AMainCameraManager::SetCameraArmLocation(FVector CameraArmTarget)
{
	const bool bXBoundOut = (CameraArmTarget.X < Bound1.X || CameraArmTarget.X > Bound2.X);
	const bool bYBoundOut = (CameraArmTarget.Z < Bound1.Y || CameraArmTarget.Z > Bound2.Y);

	if (bXBoundOut) {
		UE_LOG(LogTemp, Log, TEXT("X bound out!"));
	}
	if (bYBoundOut) {
		UE_LOG(LogTemp, Log, TEXT("Y bound out!"));
	}

	FVector AdjustedTarget = CameraArmTarget;
	if (bXBoundOut) {
		AdjustedTarget.X = CameraArm[CurrentCameraIndex]->GetActorLocation().X;
	}
	if (bYBoundOut) {
		AdjustedTarget.Z = CameraArm[CurrentCameraIndex]->GetActorLocation().Z;
	}

	CameraArm[CurrentCameraIndex]->SetActorRelativeLocation(AdjustedTarget);




}

// 사용여부 불확실한 메서드들
void AMainCameraManager::LetCameraMove(FCameraMovement mv)
{
	TargetLocation = mv.value;
	TargetRotate = mv.rotate;

	StartLocation = GetCameraArmLocation();

	isMoving = true;
}


void AMainCameraManager::MoveCamera(FVector mv, float speed)
{
	FCameraMovement newmv = { mv, speed, MainCamera[CurrentCameraIndex]->GetActorRotation(), 0};
	CameraMv.Add(newmv);
}

void AMainCameraManager::AddCameraMv(FCameraMovement mv)
{
	CameraMv.Add(mv);
}



