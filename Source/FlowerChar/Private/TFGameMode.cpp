// Fill out your copyright notice in the Description page of Project Settings.


#include "TFGameMode.h"
#include "PlayerCharacter.h"
#include "PlayerControlManager.h"


ATFGameMode::ATFGameMode()
{
	// ��Ʈ�ѷ� ����
	PlayerControllerClass = APlayerControlManager::StaticClass();

	// UClass ����, ĳ���� ����
		/*���� ���߿� ĳ���� ���� �ʿ��ϸ� ���⿡ �ִ� ��� ����*/
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		//�⺻ �� -> 3D �⺻ ĳ���ͷ� ����.
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	

}
