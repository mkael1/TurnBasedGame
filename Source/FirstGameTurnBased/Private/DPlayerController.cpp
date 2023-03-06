// Fill out your copyright notice in the Description page of Project Settings.


#include "DPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "DCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "DGameModeBase.h"


void ADPlayerController::BeginPlay()
{
	Super::BeginPlay();

	InitializePlayerParty();
}

void ADPlayerController::InitializePlayerParty()
{
	ADGameModeBase* MyMode = Cast<ADGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	AActor* PlayerStartActor = MyMode->FindPlayerStart(this);

	ADCharacter* InitialPartyMember = AddCharacterToParty(StartingPartyMember, PlayerStartActor);
	Possess(InitialPartyMember);
	SetPartyLeader(InitialPartyMember);
}


ADCharacter* ADPlayerController::AddCharacterToParty(TSubclassOf<ADCharacter> CharacterClass, AActor* PlayerStartActor = nullptr)
{
	if (PartyMembers.Num() >= MaxPartySize)
	{
		UE_LOG(LogTemp, Warning, TEXT("Trying to add a party member when you already reached the limit."));
		return nullptr;
	}

	if (!PlayerStartActor && !PartyLeader)
	{
		UE_LOG(LogTemp, Warning, TEXT("Trying to spawn a party member without a leader or a starting location."));
		return nullptr;
	}

	FVector StartingLocation;
	FRotator StartingRotation;

	// Priority is for the actor passed in and if no actor take party leader position to spawn
	if (PlayerStartActor != nullptr)
	{
		StartingLocation = PlayerStartActor->GetActorLocation();
		StartingRotation = PlayerStartActor->GetActorRotation();
	}
	else
	{
		StartingLocation = PartyLeader->GetActorLocation();
		StartingRotation = PartyLeader->GetActorRotation();
	}

	ADCharacter* PartyCharacter = Cast<ADCharacter>(GetWorld()->SpawnActor<AActor>(CharacterClass, StartingLocation, StartingRotation));

	PartyMembers.Push(PartyCharacter);
	return PartyCharacter;
}

void ADPlayerController::SetPartyLeader(ADCharacter* PartyMemberToSetLeader)
{
	for (ADCharacter* PartyMember : PartyMembers)
	{
		if (PartyMember == PartyMemberToSetLeader)
		{
			PartyLeader = PartyMemberToSetLeader;
		}
	}
}

ADCharacter* ADPlayerController::GetPartyLeader()
{
	return PartyLeader;
}

void ADPlayerController::ToggleCombatUI()
{
	if (!ensure(CombatWidgetClass))
	{
		return;
	}

	if (CombatWidgetInstance && CombatWidgetInstance->IsInViewport())
	{
		CombatWidgetInstance->RemoveFromParent();
		CombatWidgetInstance = nullptr;
		bShowMouseCursor = false;
		SetInputMode(FInputModeGameOnly());
	}

	CombatWidgetInstance = CreateWidget<UUserWidget>(this, CombatWidgetClass);
	if (CombatWidgetInstance)
	{
		CombatWidgetInstance->AddToViewport(10);
		bShowMouseCursor = true;
		SetInputMode(FInputModeUIOnly());
	}
}

