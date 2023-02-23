// Fill out your copyright notice in the Description page of Project Settings.


#include "DGameModeBase.h"
#include "DGameStateBase.h"
#include "GameFramework/CharacterMovementComponent.h"


void ADGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	GameStateInstance = GetGameState<ADGameState>();


	EnterCombat();
}

void ADGameModeBase::EnterCombat()
{

	APawn* Player = GetWorld()->GetFirstPlayerController()->GetPawn();
	UCharacterMovementComponent* CharMovement = Cast<UCharacterMovementComponent>(Player->GetComponentByClass(UCharacterMovementComponent::StaticClass()));
	CharMovement->DisableMovement();

	InitializeTeams(Player);

	StartCombat();
}

void ADGameModeBase::InitializeTeams(APawn* Player)
{

	GameStateInstance->SetTeamOne(Player);
	GameStateInstance->SetTeamTwo(Player);
}

void ADGameModeBase::StartCombat()
{
	GameStateInstance->ChangeTurn();
}

void ADGameModeBase::FinishPlayerCombatTurn(APawn* Player)
{
	if (GameStateInstance->GetCurrentTurn() == Player)
	{
		GameStateInstance->ChangeTurn();
	}
}

