// Fill out your copyright notice in the Description page of Project Settings.


#include "ApporachInteractTrigger.h"

AApporachInteractTrigger::AApporachInteractTrigger()
{
	// 충돌 감지 박스 생성
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	SetRootComponent(BoxCollider);

	// 콜라이더 박스 사이즈 설정
	BoxCollider->SetBoxExtent(ColliderBoxSize);

	// 공간 기반으로 충돌 감지하도록 설정
	BoxCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxCollider->SetCollisionObjectType(ECC_WorldDynamic); // 라인 트레이스 대상


	// 모든 채널 무시 후 ECC_Visibility만 Block
	BoxCollider->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxCollider->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap); // 채널별로 뭔가가 다르다고? 
	BoxCollider->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	//델리게이트 연결.
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AApporachInteractTrigger::TriggerBeginOverlap);
	BoxCollider->OnComponentEndOverlap.AddDynamic(this, &AApporachInteractTrigger::TriggerEndOverlap);

	// KeyNoticeWidget 생성
	KeyNoticeWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("KeyNoticeWidget"));
	KeyNoticeWidget->SetupAttachment(RootComponent);
}
void AApporachInteractTrigger::BeginPlay()
{
	Super::BeginPlay();
	
	//=======================================
	// KeyNotation 설정
	//==========================================
	if (bShowKeyNoticeWidget) {
		// 만약 설정 켜져있으면
		KeyNoticeWidget->SetRelativeLocation(KeyNoticeWidgetVector);

		KeyNoticeWidget->SetWidgetClass(KeyNoticeWidgetClass);// 위젯 클래스 설정
		KeyNoticeWidget->SetWidgetSpace(EWidgetSpace::Screen);//스크린 설정
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
	if (IsValid(KeyNoticeWidget)) { // IsValid()는 null 체크와 PendingKill 상태까지 안전하게 확인해줍니다.
		KeyNoticeWidget->SetVisibility(true);
	}
	
}

void AApporachInteractTrigger::HideKeyNoticeWidget()
{
	if (IsValid(KeyNoticeWidget)) { // IsValid()는 null 체크와 PendingKill 상태까지 안전하게 확인해줍니다.
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




