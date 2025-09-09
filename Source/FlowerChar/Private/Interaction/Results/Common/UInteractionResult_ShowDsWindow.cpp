// Fill out your copyright notice in the Description page of Project Settings.


#include "Interaction/Results/Common/UInteractionResult_ShowDsWindow.h"
#include "Widget/WorldItemDescriptionWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"

void UUInteractionResult_ShowDsWindow::Execute(APlayerCharacter* Player)
{
	if (!IsValid(DescriptionWidgetInstance))
	{
		DescriptionWidgetInstance = CreateWidget<UWorldItemDescriptionWidget>(GetWorld(), DescriptionWidget);

		// 위젯 생성에 실패하면 아무것도 하지 않고 함수를 종료합니다. (가드 클로즈)
		if (!DescriptionWidgetInstance)
		{
			UE_LOG(LogTemp, Error, TEXT("DescriptionWidget을 생성할 수 없습니다!"));
			return;
		}
	}

	// 2. 위젯이 뷰포트에 나와있지 않은 경우에만 보이도록 처리합니다.
	if (!DescriptionWidgetInstance->IsInViewport())
	{
		// 3. 데이터를 설정하고 뷰포트에 추가합니다.
		// 이 로직은 위젯이 새로 생성됐든, 재사용되든 항상 실행됩니다.
		DescriptionWidgetInstance->SetTitleText(Title);
		DescriptionWidgetInstance->SetContentsText(Contents);
		DescriptionWidgetInstance->AddToViewport();
	}
	
}



