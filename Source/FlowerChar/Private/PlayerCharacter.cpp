// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "PlayerControlManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{

	// 틱 활성화
	PrimaryActorTick.bCanEverTick = true;

 	/** 캐릭터 변수값 기본 세팅 */
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f); // 콜라이더 초기화

	bUseControllerRotationPitch = false; // 카메라 움직임 따라서 회전하지 않도록 조치
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // 캐릭터가 움직이는 방향과 시선이 똑같도록 처리
	GetCharacterMovement()->bConstrainToPlane = true; // 평면을 따라가도록 처리
	GetCharacterMovement()->bSnapToPlaneAtStart = true; // 평면 이상하게 벗어가면 이상해지지 않도록 조치

	/** Default 카메라 셀카봉 생성*/
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	CameraBoom->SetupAttachment(GetCapsuleComponent()); // 캡슐 오브젝트 기본 할당, 따라다닐 오브젝트 확인
	CameraBoom->TargetArmLength = 500.f; //셀카봉 길이
	CameraBoom->bUsePawnControlRotation = false; // 카메라 로테이션에 폰이 따라갈지 여부 결정 -> X

	// 카메라 설정
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);
	FollowCamera->bUsePawnControlRotation = false;


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


}

// 처음 시작됐을 때 작동.
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();



	
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
	}
	
}

void APlayerCharacter::Move(const FInputActionValue& Value) {
	//실제 Move쪽 구현 

	FVector Dest;
	if (Controller != nullptr && Cast<APlayerControlManager>(GetController())->GetRightClickVector(Dest)) {
		float const Distance = FVector::Dist(Dest, GetActorLocation());//거리 구하기
		if (Distance > 120.f) {
			// 위치 
			
			ShowDesCursor(Dest); //커서 보이게 하기
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), Dest);
			HideDesCursor(Dest); //커서 안 보이게 하기.
			
		}

	}

	

}

void APlayerCharacter::ShowDesCursor(const FVector Destination)
{
	//움직이는 쪽으로 커서 생성.
}

void APlayerCharacter::HideDesCursor(const FVector Destination)
{
	//커서 삭제
}

