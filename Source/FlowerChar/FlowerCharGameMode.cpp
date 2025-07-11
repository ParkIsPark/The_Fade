// Copyright Epic Games, Inc. All Rights Reserved.

//�⺻ ���
#include "FlowerCharGameMode.h"
#include "FlowerCharCharacter.h"
#include "UObject/ConstructorHelpers.h"




AFlowerCharGameMode::AFlowerCharGameMode()
{
	//ĳ���� �⺻ �Ҵ�
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

