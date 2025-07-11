// Fill out your copyright notice in the Description page of Project Settings.


#include "TFGameMode.h"
#include "PlayerCharacter.h"
#include "PlayerControlManager.h"


ATFGameMode::ATFGameMode()
{
	// 컨트롤러 설정
	PlayerControllerClass = APlayerControlManager::StaticClass();

	// UClass 설정, 캐릭터 설정
		/*만일 나중에 캐릭터 수정 필요하면 여기에 있는 경로 수정*/
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		//기본 폰 -> 3D 기본 캐릭터로 설정.
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	

}
