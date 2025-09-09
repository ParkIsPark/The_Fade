// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "PlayerControlManager.h"
#include "ObjectManager.h" // 커서 스폰 위함
#include "MainCameraManager.h" // 메인 카메라 조작 위함. 
#include "ApporachInteractTrigger.h" // 순환참조 문제 해결
#include "GameFramework/CharacterMovementComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{

	// 틱 활성화
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

 	/** 캐릭터 변수값 기본 세팅 */
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f); // 콜라이더 초기화

	bUseControllerRotationPitch = false; // 컨트롤러 움직임 따라 회전하지 않도록 조치. 
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true; // 본인 움직임의 속도 따라 움직이도록 조치. 

	GetCharacterMovement()->RotationRate = FRotator(0.0f, 640.0f, 0.0f); // 캐릭터가 움직이는 방향과 시선이 똑같도록 처리
	GetCharacterMovement()->bConstrainToPlane = true; // 평면을 따라가도록 처리
	GetCharacterMovement()->bSnapToPlaneAtStart = true; // 평면 이상하게 벗어가면 이상해지지 않도록 조치



	// EnhancedInputContext 활성화 루틴, 한번만 가져오므로 static 사용
	static ConstructorHelpers::FObjectFinder<UInputMappingContext>DEFAULT_CONTEXT
	(TEXT("/Game/Input/Mapping/TF_MainPlayKey")); // 메인 플레이 키 매핑된 정보 가져오기
	if (DEFAULT_CONTEXT.Succeeded())
	{
		DefaultMappingContext = DEFAULT_CONTEXT.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction>TF_MOVE
	(TEXT("/Game/Input/Action/TF_move")); // MoveAction 가져오기.
	if (TF_MOVE.Succeeded())
	{
		MoveAction = TF_MOVE.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction>TF_CameraMove
	(TEXT("/Game/Input/Action/TF_CameraMove")); // CameraMoveAction 가져오기.
	if (TF_MOVE.Succeeded())
	{
		CameraMoveAction = TF_CameraMove.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction>TF_Interative
	(TEXT("/Game/Input/Action/TF_Interactive")); // Interative 가져오기
	if (TF_Interative.Succeeded())
	{
		InteractAction = TF_Interative.Object;
	}




}

// 처음 시작됐을 때 작동.
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();


	//오브젝트 매니저 연결
	for ( TActorIterator<AObjectManager> It(GetWorld()); It; ++It){
		ObjectManager = *It;

		//연결 후 오브젝트 매니저에서 커서 꺼내오는 작업.
		FActorSpawnParameters SpawnParams;
		SpawnParams.Name = FName(TEXT("Cursor_mesh")); // 커서 스폰

		Cursor = GetWorld()->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass(), SpawnParams);
		UStaticMeshComponent* Cursor_Comp = Cursor->GetStaticMeshComponent(); // 매쉬 컴포넌트 받아오기
		Cursor_Comp->SetStaticMesh(ObjectManager->GetCommonMesh(TEXT("Cursor"))); // 커서 매쉬 설정

		Cursor->SetMobility(EComponentMobility::Movable);//움직일 수 있게 설정
		Cursor->SetActorLocation(GetActorLocation()); // 위치 설정
		Cursor->SetActorScale3D(FVector(1.0f)); // 크기 설정
		Cursor_Comp->SetVisibility(false); // 안 보이게 설정(풀링)
		//커서 설정
		break;

	}

	// 메인 카메라 매니저 연결

	for (TActorIterator<AMainCameraManager> It(GetWorld()); It; ++It) {
		MainCameraManager = *It;

	}

	
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//목적지 확인한 상태인지 계속 체크
	IsArrive();

	//상호작용 가능한 상태인지 계속 확인
	isInteractable();
	
	

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// 컨트롤러 <-> 매핑 Context 연결 루틴
	//기본적으로 부여받은 PlayerControlManager 불러오기.
	if (APlayerController* PlayerController = Cast<APlayerControlManager>(GetController()))
	{
		//해당 컨트롤러에 inputMappingContext 붙여넣기
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);// 매핑
		}
	}

	//매개변수로 주어진 inputComponent -> EnhancedInputComponent 로 업그레이드.
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// 오류해결 -> FInputActionValue로 받아줘야 했음. 
		
		//좌클릭 바인딩
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Started, this, &APlayerCharacter::Move);

		//미들클릭 바인딩
		EnhancedInputComponent->BindAction(CameraMoveAction, ETriggerEvent::Started, this, &APlayerCharacter::CameraMoveStart);
		EnhancedInputComponent->BindAction(CameraMoveAction, ETriggerEvent::Ongoing, this, &APlayerCharacter::CameraMove);//미들클릭 카메라 무빙 바인드
		//Ongoing -> 지속적으로 움직여야
		EnhancedInputComponent->BindAction(CameraMoveAction, ETriggerEvent::Completed, this, &APlayerCharacter::CameraMoveFinish);


		//E키 바인딩
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &APlayerCharacter::InteractObj);
	}
	
}



//좌클릭 -> Move 구현.
void APlayerCharacter::Move(const FInputActionValue& Value) {


	if (Controller != nullptr && Cast<APlayerControlManager>(GetController())->GetClickVector(Dest)) {
		float const Distance = FVector::Dist(Dest, GetActorLocation());//거리 구하기
		if (Distance > 120.f) {
			// 위치 

			//모든 커서 지우기

			//커서 쪽은 일단 비활성화(8/9) 
			HideDesCursor(Dest);
			ShowDesCursor(Dest); //커서 보이게 하기
			bMovingToInteractActor = false;
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), Dest);
		
			
		}

	}

	

}

// 상호작용 오브젝트로 
void APlayerCharacter::MoveToInteractTarget()
{
	FVector TargetLC = InteractTarget->GetActorLocation();
	if (Controller != nullptr ) {
		float const Distance = FVector::Dist(TargetLC, GetActorLocation());//거리 구하기
		if (Distance > 120.f) {
			// 위치 
			bMovingToInteractActor = true;
			HideDesCursor(TargetLC);
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), TargetLC);
			


		}

	}
}

//커서 보이기 -> 커서 쪽은 일단 비활성화(8/9)
void APlayerCharacter::ShowDesCursor(const FVector Destination)
{
	
	//UStaticMeshComponent* Cursor_Comp = Cursor->GetStaticMeshComponent(); // 매쉬 컴포넌트 받아오기
	//Cursor->SetActorLocation(FVector(Destination.X, Destination.Y, Destination.Z + 1.0f));//기본 위치 설정
	//Cursor_Comp->SetVisibility(true); // 보이게 설정(풀링)
	//Cursor_Comp->SetHiddenInGame(false);



}

//커서 없애기 -> 커서 쪽은 일단 비활성(8/9)
void APlayerCharacter::HideDesCursor(const FVector Destination)
{

	UStaticMeshComponent* Cursor_Comp = Cursor->GetStaticMeshComponent(); // 매쉬 컴포넌트 받아오기
	Cursor_Comp->SetVisibility(false); // 안 보이게 설정(풀링)
	Cursor_Comp->SetHiddenInGame(true); // 커서 삭제


}

//도착했는지 계속 체크
void APlayerCharacter::IsArrive()
{
	
	if (GetVelocity().Size() == 0.0f && isMoving) {
		//계속해서 목적지에 도달했는지 확인, 속도 벡터 크기 구하기
		HideDesCursor(Dest); //커서 안 보이게 하기. -> 개꼼수, MoveTo 델리게이트 활용 안할거야 ㅅㅂ
		isMoving = false;
	}
	if (GetVelocity().Size() > 0.0f) {
		isMoving = true;
	}
}

//우클릭 -> 카메라 움직임 드래그
void APlayerCharacter::CameraMoveStart(const FInputActionValue& Value)
{
	if (Controller != nullptr && Cast<APlayerControlManager>(GetController())->GetMousePosition(ClickVector.X, ClickVector.Y)) {
		isDrag = true;
		PostClickVector = ClickVector;
	}
	
}

void APlayerCharacter::CameraMove(const FInputActionValue& Value)
{
	if (Controller != nullptr && Cast<APlayerControlManager>(GetController())->GetMousePosition(ClickVector.X, ClickVector.Y)) {
		if (isDrag)
		{
			//위의 GetMousePosition은 화면 기준으로 스크린 2D 기준의 좌표를 받아오는 것. 
			float speed = (ClickVector - PostClickVector).Size();

			FVector2D MouseDelta = (ClickVector - PostClickVector); // 마우스의 움직임은 현재 좌표 - 이전 좌표의 벡터.



			FVector CameraArmVector = MainCameraManager->GetCameraArmLocation(); // 카메라 로케이션 얻어오기. 


			FVector Movement = FVector(-MouseDelta.X, 0.0f, MouseDelta.Y); // 움직임은 x, y좌표
			
			speed = FMath::Clamp(speed, 0.0f, 2.0f);


			FVector TargetLocation = CameraArmVector + Movement * speed; // 보정된 스피드값으로 이동 위치 결정. 

			MainCameraManager->SetCameraArmLocation(TargetLocation);

			
			PostClickVector = ClickVector; // 드래그 중 실시간으로 PostClickVector 받도록 변경
		}
		
		
	}
}

void APlayerCharacter::CameraMoveFinish(const FInputActionValue& Value)
{
	if (Controller != nullptr && Cast<APlayerControlManager>(GetController())->GetMousePosition(ClickVector.X, ClickVector.Y)) {
		isDrag = false;
		PostClickVector = ClickVector;
	}
}

//E키 -> 상호작용.

void APlayerCharacter::InteractObj(const FInputActionValue& Value)
{
	if (InteractFunc)
	{
		// 상호작용 함수가 존재하면 실행
		InteractFunc();
	}
	else if (InteractTarget)
	{
		//함수가 없고 대상이 있으면 이동
		MoveToInteractTarget();
	}

}

void APlayerCharacter::isInteractable()
{
	if (!isTriggered) {
		InteractFunc = nullptr; // 상호작용 함수 nullptr로 바꿔버리기.
	}
}

