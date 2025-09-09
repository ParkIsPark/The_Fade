// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "PlayerControlManager.h"
#include "ObjectManager.h" // Ŀ�� ���� ����
#include "MainCameraManager.h" // ���� ī�޶� ���� ����. 
#include "ApporachInteractTrigger.h" // ��ȯ���� ���� �ذ�
#include "GameFramework/CharacterMovementComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{

	// ƽ Ȱ��ȭ
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

 	/** ĳ���� ������ �⺻ ���� */
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f); // �ݶ��̴� �ʱ�ȭ

	bUseControllerRotationPitch = false; // ��Ʈ�ѷ� ������ ���� ȸ������ �ʵ��� ��ġ. 
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true; // ���� �������� �ӵ� ���� �����̵��� ��ġ. 

	GetCharacterMovement()->RotationRate = FRotator(0.0f, 640.0f, 0.0f); // ĳ���Ͱ� �����̴� ����� �ü��� �Ȱ����� ó��
	GetCharacterMovement()->bConstrainToPlane = true; // ����� ���󰡵��� ó��
	GetCharacterMovement()->bSnapToPlaneAtStart = true; // ��� �̻��ϰ� ����� �̻������� �ʵ��� ��ġ



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
	static ConstructorHelpers::FObjectFinder<UInputAction>TF_CameraMove
	(TEXT("/Game/Input/Action/TF_CameraMove")); // CameraMoveAction ��������.
	if (TF_MOVE.Succeeded())
	{
		CameraMoveAction = TF_CameraMove.Object;
	}
	static ConstructorHelpers::FObjectFinder<UInputAction>TF_Interative
	(TEXT("/Game/Input/Action/TF_Interactive")); // Interative ��������
	if (TF_Interative.Succeeded())
	{
		InteractAction = TF_Interative.Object;
	}




}

// ó�� ���۵��� �� �۵�.
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();


	//������Ʈ �Ŵ��� ����
	for ( TActorIterator<AObjectManager> It(GetWorld()); It; ++It){
		ObjectManager = *It;

		//���� �� ������Ʈ �Ŵ������� Ŀ�� �������� �۾�.
		FActorSpawnParameters SpawnParams;
		SpawnParams.Name = FName(TEXT("Cursor_mesh")); // Ŀ�� ����

		Cursor = GetWorld()->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass(), SpawnParams);
		UStaticMeshComponent* Cursor_Comp = Cursor->GetStaticMeshComponent(); // �Ž� ������Ʈ �޾ƿ���
		Cursor_Comp->SetStaticMesh(ObjectManager->GetCommonMesh(TEXT("Cursor"))); // Ŀ�� �Ž� ����

		Cursor->SetMobility(EComponentMobility::Movable);//������ �� �ְ� ����
		Cursor->SetActorLocation(GetActorLocation()); // ��ġ ����
		Cursor->SetActorScale3D(FVector(1.0f)); // ũ�� ����
		Cursor_Comp->SetVisibility(false); // �� ���̰� ����(Ǯ��)
		//Ŀ�� ����
		break;

	}

	// ���� ī�޶� �Ŵ��� ����

	for (TActorIterator<AMainCameraManager> It(GetWorld()); It; ++It) {
		MainCameraManager = *It;

	}

	
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//������ Ȯ���� �������� ��� üũ
	IsArrive();

	//��ȣ�ۿ� ������ �������� ��� Ȯ��
	isInteractable();
	
	

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
		
		//��Ŭ�� ���ε�
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Started, this, &APlayerCharacter::Move);

		//�̵�Ŭ�� ���ε�
		EnhancedInputComponent->BindAction(CameraMoveAction, ETriggerEvent::Started, this, &APlayerCharacter::CameraMoveStart);
		EnhancedInputComponent->BindAction(CameraMoveAction, ETriggerEvent::Ongoing, this, &APlayerCharacter::CameraMove);//�̵�Ŭ�� ī�޶� ���� ���ε�
		//Ongoing -> ���������� ��������
		EnhancedInputComponent->BindAction(CameraMoveAction, ETriggerEvent::Completed, this, &APlayerCharacter::CameraMoveFinish);


		//EŰ ���ε�
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &APlayerCharacter::InteractObj);
	}
	
}



//��Ŭ�� -> Move ����.
void APlayerCharacter::Move(const FInputActionValue& Value) {


	if (Controller != nullptr && Cast<APlayerControlManager>(GetController())->GetClickVector(Dest)) {
		float const Distance = FVector::Dist(Dest, GetActorLocation());//�Ÿ� ���ϱ�
		if (Distance > 120.f) {
			// ��ġ 

			//��� Ŀ�� �����

			//Ŀ�� ���� �ϴ� ��Ȱ��ȭ(8/9) 
			HideDesCursor(Dest);
			ShowDesCursor(Dest); //Ŀ�� ���̰� �ϱ�
			bMovingToInteractActor = false;
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), Dest);
		
			
		}

	}

	

}

// ��ȣ�ۿ� ������Ʈ�� 
void APlayerCharacter::MoveToInteractTarget()
{
	FVector TargetLC = InteractTarget->GetActorLocation();
	if (Controller != nullptr ) {
		float const Distance = FVector::Dist(TargetLC, GetActorLocation());//�Ÿ� ���ϱ�
		if (Distance > 120.f) {
			// ��ġ 
			bMovingToInteractActor = true;
			HideDesCursor(TargetLC);
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(GetController(), TargetLC);
			


		}

	}
}

//Ŀ�� ���̱� -> Ŀ�� ���� �ϴ� ��Ȱ��ȭ(8/9)
void APlayerCharacter::ShowDesCursor(const FVector Destination)
{
	
	//UStaticMeshComponent* Cursor_Comp = Cursor->GetStaticMeshComponent(); // �Ž� ������Ʈ �޾ƿ���
	//Cursor->SetActorLocation(FVector(Destination.X, Destination.Y, Destination.Z + 1.0f));//�⺻ ��ġ ����
	//Cursor_Comp->SetVisibility(true); // ���̰� ����(Ǯ��)
	//Cursor_Comp->SetHiddenInGame(false);



}

//Ŀ�� ���ֱ� -> Ŀ�� ���� �ϴ� ��Ȱ��(8/9)
void APlayerCharacter::HideDesCursor(const FVector Destination)
{

	UStaticMeshComponent* Cursor_Comp = Cursor->GetStaticMeshComponent(); // �Ž� ������Ʈ �޾ƿ���
	Cursor_Comp->SetVisibility(false); // �� ���̰� ����(Ǯ��)
	Cursor_Comp->SetHiddenInGame(true); // Ŀ�� ����


}

//�����ߴ��� ��� üũ
void APlayerCharacter::IsArrive()
{
	
	if (GetVelocity().Size() == 0.0f && isMoving) {
		//����ؼ� �������� �����ߴ��� Ȯ��, �ӵ� ���� ũ�� ���ϱ�
		HideDesCursor(Dest); //Ŀ�� �� ���̰� �ϱ�. -> ���ļ�, MoveTo ��������Ʈ Ȱ�� ���Ұž� ����
		isMoving = false;
	}
	if (GetVelocity().Size() > 0.0f) {
		isMoving = true;
	}
}

//��Ŭ�� -> ī�޶� ������ �巡��
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
			//���� GetMousePosition�� ȭ�� �������� ��ũ�� 2D ������ ��ǥ�� �޾ƿ��� ��. 
			float speed = (ClickVector - PostClickVector).Size();

			FVector2D MouseDelta = (ClickVector - PostClickVector); // ���콺�� �������� ���� ��ǥ - ���� ��ǥ�� ����.



			FVector CameraArmVector = MainCameraManager->GetCameraArmLocation(); // ī�޶� �����̼� ������. 


			FVector Movement = FVector(-MouseDelta.X, 0.0f, MouseDelta.Y); // �������� x, y��ǥ
			
			speed = FMath::Clamp(speed, 0.0f, 2.0f);


			FVector TargetLocation = CameraArmVector + Movement * speed; // ������ ���ǵ尪���� �̵� ��ġ ����. 

			MainCameraManager->SetCameraArmLocation(TargetLocation);

			
			PostClickVector = ClickVector; // �巡�� �� �ǽð����� PostClickVector �޵��� ����
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

//EŰ -> ��ȣ�ۿ�.

void APlayerCharacter::InteractObj(const FInputActionValue& Value)
{
	if (InteractFunc)
	{
		// ��ȣ�ۿ� �Լ��� �����ϸ� ����
		InteractFunc();
	}
	else if (InteractTarget)
	{
		//�Լ��� ���� ����� ������ �̵�
		MoveToInteractTarget();
	}

}

void APlayerCharacter::isInteractable()
{
	if (!isTriggered) {
		InteractFunc = nullptr; // ��ȣ�ۿ� �Լ� nullptr�� �ٲ������.
	}
}

