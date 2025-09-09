// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Framework/WorldItemBase.h"
#include "Interaction/Framework/InteractionComponent.h"



AWorldItemBase::AWorldItemBase()
{
	InteractionCompInst = CreateDefaultSubobject<UInteractionComponent>(TEXT("Interact"));
}


void AWorldItemBase::OnInteract()
{
	if (Player != nullptr) {
		InteractionCompInst->AttemptInteraction(Player);
		UE_LOG(LogTemp, Log, TEXT("[WorldItem] Mouse Cursor On"));
	}
}
