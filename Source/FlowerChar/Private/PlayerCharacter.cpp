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

	// ƽ Ȱ��ȭ
	PrimaryActorTick.bCanEverTick = true;

 	/** ĳ���� ������ �⺻ ���� */
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f); // �ݶ��̴� �ʱ�ȭ

	bUseControllerRotationPitch = false; // ī�޶� ������ ���� ȸ������ �ʵ��� ��ġ
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ĳ���Ͱ� �����̴� ����� �ü��� �Ȱ����� ó��
	GetCharacterMovement()->bConstrainToPlane = true; // ����� ���󰡵��� ó��
	GetCharacterMovement()->bSnapToPlaneAtStart = true; // ��� �̻��ϰ� ����� �̻������� �ʵ��� ��ġ

	/** Default ī�޶� ��ī�� ����*/
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	CameraBoom->SetupAttachment(GetCapsuleComponent()); // ĸ�� ������Ʈ �⺻ �Ҵ�, ����ٴ� ������Ʈ Ȯ��
	CameraBoom->TargetArmLength = 500.f; //��ī�� ����
	CameraBoom->bUsePawnControlRotation = false; // ī�޶� �����̼ǿ� ���� ������ ���� ���� -> X

	// ī�޶� ����
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);
	FollowCamera->bUsePawnControlRotation = false;


	// EnhancedInputContext Ȱ��ȭ ��ƾ, �ѹ��� �������Ƿ� static ���
	static ConstructorHelpers::FObjectFinder<UInputMappingContext>DEFAULT_CONTEXT
	(TEXT("/Game/Input/Mapping/TF_MainPlayKey")); // ���� �÷��� Ű ���ε� ���� ��������
	if (DEFAULT_CONTEXT.Succeeded())
	{
		DefaultMappingContext = DEFAULT_CONTEXT.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction>TF_MOVE
	(TEXT("/Game/Input/Action/TF_move")); // MoveAction ��������.
	if (TF_MOVE.Succeeded())
	{
		MoveAction = TF_MOVE.Object;
	}


}

// ó�� ���۵��� �� �۵�.
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

	// ��Ʈ�ѷ� <-> ���� Context ���� ��ƾ
	//�⺻������ �ο����� PlayerControlManager �ҷ�����.
	if (APlayerController* PlayerController = Cast<APlayerControlManager>(GetController()))
	{
		//�ش� ��Ʈ�ѷ��� inputMappingContext �ٿ��ֱ�
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);// ����
		}
	}

	//�Ű������� �־��� inputComponent -> EnhancedInputComponent �� ���׷��̵�.
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// �����ذ� -> FInputActionValue�� �޾���� ����. 
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
	}
	
}

void APlayerCharacter::Move(const FInputActionValue& Value) {
	//���� Move�� ���� 

	FVector Dest;
	if (Controller != nullptr && Cast<APlayerControlManager>(GetController())->GetRightClickVector(Dest)) {
		float const Distance = FVector::Dist(Dest, GetActorLocation());//�Ÿ� ���ϱ�
		if (Distance > 120.f) {
			// ��ġ 
			
			ShowDesCursor(Dest); //Ŀ�� ���̰� �ϱ�
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), Dest);
			HideDesCursor(Dest); //Ŀ�� �� ���̰� �ϱ�.
			
		}

	}

	

}

void APlayerCharacter::ShowDesCursor(const FVector Destination)
{
	//�����̴� ������ Ŀ�� ����.
}

void APlayerCharacter::HideDesCursor(const FVector Destination)
{
	//Ŀ�� ����
}

