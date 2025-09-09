// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraMovementStruct.h"

// Sets default values
ACameraMovementStruct::ACameraMovementStruct()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACameraMovementStruct::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACameraMovementStruct::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

