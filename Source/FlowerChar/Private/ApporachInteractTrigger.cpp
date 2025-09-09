// Fill out your copyright notice in the Description page of Project Settings.


#include "ApporachInteractTrigger.h"

AApporachInteractTrigger::AApporachInteractTrigger()
{
	// �浹 ���� �ڽ� ����
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	SetRootComponent(BoxCollider);

	// �ݶ��̴� �ڽ� ������ ����
	BoxCollider->SetBoxExtent(ColliderBoxSize);

	// ���� ������� �浹 �����ϵ��� ����
	BoxCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxCollider->SetCollisionObjectType(ECC_WorldDynamic); // ���� Ʈ���̽� ���


	// ��� ä�� ���� �� ECC_Visibility�� Block
	BoxCollider->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxCollider->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap); // ä�κ��� ������ �ٸ��ٰ�? 
	BoxCollider->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	//��������Ʈ ����.
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AApporachInteractTrigger::TriggerBeginOverlap);
	BoxCollider->OnComponentEndOverlap.AddDynamic(this, &AApporachInteractTrigger::TriggerEndOverlap);

	// KeyNoticeWidget ����
	KeyNoticeWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("KeyNoticeWidget"));
	KeyNoticeWidget->SetupAttachment(RootComponent);
}
void AApporachInteractTrigger::BeginPlay()
{
	Super::BeginPlay();
	
	//=======================================
	// KeyNotation ����
	//==========================================
	if (bShowKeyNoticeWidget) {
		// ���� ���� ����������
		KeyNoticeWidget->SetRelativeLocation(KeyNoticeWidgetVector);

		KeyNoticeWidget->SetWidgetClass(KeyNoticeWidgetClass);// ���� Ŭ���� ����
		KeyNoticeWidget->SetWidgetSpace(EWidgetSpace::Screen);//��ũ�� ����
		KeyNoticeWidget->SetDrawSize(KeyNoticeWidgetSize);
		KeyNoticeWidget->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		HideKeyNoticeWidget();
	}
}
void AApporachInteractTrigger::TriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlapped Actor: %s"), *OtherActor->GetName());

	Player = Cast<APlayerCharacter>(OtherActor);
	if (Player != nullptr) {
		OnPlayerTrigger();
	}



}

void AApporachInteractTrigger::TriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlapped Actor: %s"), *OtherActor->GetName());
	Player = Cast<APlayerCharacter>(OtherActor);
	if (Player != nullptr && Cast<APlayerCharacter>(OtherActor)) {
		OnPlayerTriggerEnd();
	}
	Player = nullptr;
}
void AApporachInteractTrigger::OnInteract()
{
}

void AApporachInteractTrigger::ShowKeyNoticeWidget()
{
	if (IsValid(KeyNoticeWidget)) { // IsValid()�� null üũ�� PendingKill ���±��� �����ϰ� Ȯ�����ݴϴ�.
		KeyNoticeWidget->SetVisibility(true);
	}
	
}

void AApporachInteractTrigger::HideKeyNoticeWidget()
{
	if (IsValid(KeyNoticeWidget)) { // IsValid()�� null üũ�� PendingKill ���±��� �����ϰ� Ȯ�����ݴϴ�.
		KeyNoticeWidget->SetVisibility(false);
	}
}

void AApporachInteractTrigger::OnPlayerTrigger()
{
	Player->isTriggered = true;
	Player->InteractFunc = [this]()
	{
		this->OnInteract();
	};
}

void AApporachInteractTrigger::OnPlayerTriggerEnd()
{
	Player->isTriggered = false;
}

void AApporachInteractTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsUnderMouse) {
		ShowKeyNoticeWidget();
	}
	else {
		HideKeyNoticeWidget();
	}

}




