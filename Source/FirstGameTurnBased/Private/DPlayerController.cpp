// Fill out your copyright notice in the Description page of Project Settings.


#include "DPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "DCharacter.h"


void ADPlayerController::BeginPlay()
{
	Super::BeginPlay();

	for (TSubclassOf<ADCharacter> Character : StartingPartyMembers)
	{
		AddCharacterToParty(Character);
	}
}


void ADPlayerController::AddCharacterToParty(TSubclassOf<ADCharacter> CharacterClass)
{
	if (PartyMembers.Num() >= MaxPartySize)
	{
		UE_LOG(LogTemp, Warning, TEXT("Trying to add a party member when you already reached the limit."));
	}

	ADCharacter* Character = Cast<ADCharacter>(GetWorld()->SpawnActor(CharacterClass));
	
	PartyMembers.Push(Character);
}



void ADPlayerController::ToggleCombatUI()
{
	if (!ensure(CombatWidgetClass)) {
		return;
	}

	if (CombatWidgetInstance && CombatWidgetInstance->IsInViewport()) {
		CombatWidgetInstance->RemoveFromParent();
		CombatWidgetInstance = nullptr;
		bShowMouseCursor = false;
		SetInputMode(FInputModeGameOnly());
	}

	CombatWidgetInstance = CreateWidget<UUserWidget>(this, CombatWidgetClass);
	if (CombatWidgetInstance) {
		CombatWidgetInstance->AddToViewport(10);
		bShowMouseCursor = true;
		SetInputMode(FInputModeUIOnly());
	}
}

