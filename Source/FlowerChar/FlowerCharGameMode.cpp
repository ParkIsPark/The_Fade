// Copyright Epic Games, Inc. All Rights Reserved.

//기본 헤더
#include "FlowerCharGameMode.h"
#include "FlowerCharCharacter.h"
#include "UObject/ConstructorHelpers.h"




AFlowerCharGameMode::AFlowerCharGameMode()
{
	//캐릭터 기본 할당
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

