// Fill out your copyright notice in the Description page of Project Settings.

//모든 Trigger형 클래스들의 부모가 되는 클래스
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerCharacter.h"
#include "TFTrigger.generated.h"

UCLASS()
class FLOWERCHAR_API ATFTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATFTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual void OnPlayerTrigger() PURE_VIRTUAL(ATFTrigger::OnPlayerTrigger, ); // 트리거 시작 
	virtual void OnPlayerTriggerEnd() PURE_VIRTUAL(ATFTrigger::OnPlayerTriggerEnd, ); // 트리거 종료. 

};
