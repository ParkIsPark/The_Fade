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

		// ���� ������ �����ϸ� �ƹ��͵� ���� �ʰ� �Լ��� �����մϴ�. (���� Ŭ����)
		if (!DescriptionWidgetInstance)
		{
			UE_LOG(LogTemp, Error, TEXT("DescriptionWidget�� ������ �� �����ϴ�!"));
			return;
		}
	}

	// 2. ������ ����Ʈ�� �������� ���� ��쿡�� ���̵��� ó���մϴ�.
	if (!DescriptionWidgetInstance->IsInViewport())
	{
		// 3. �����͸� �����ϰ� ����Ʈ�� �߰��մϴ�.
		// �� ������ ������ ���� �����Ƶ�, ����ǵ� �׻� ����˴ϴ�.
		DescriptionWidgetInstance->SetTitleText(Title);
		DescriptionWidgetInstance->SetContentsText(Contents);
		DescriptionWidgetInstance->AddToViewport();
	}
	
}



