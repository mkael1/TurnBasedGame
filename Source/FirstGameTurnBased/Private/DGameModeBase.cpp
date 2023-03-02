// Fill out your copyright notice in the Description page of Project Settings.


#include "DGameModeBase.h"
#include "DGameStateBase.h"
#include "GameFramework/CharacterMovementComponent.h"


void ADGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	GameStateInstance = GetGameState<ADGameState>();

}

void ADGameModeBase::EnterCombat(AActor* Player, AActor* Enemy)
{
	OnCombatStarted.Broadcast(Player, Enemy);

	APawn* PlayerPawn = Cast<APawn>(Player);

	InitializeTeams(PlayerPawn);

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
	if (!Player) {
		return;
	}

	APawn* OldActor = GameStateInstance->GetCurrentTurn();
	if (OldActor == Player)
	{
		GameStateInstance->ChangeTurn();
		OnTurnChanged.Broadcast(OldActor, Player, GameStateInstance->GetTurnCount());
	}
}

void ADGameModeBase::DevSwitchTurn()
{
	GameStateInstance->ChangeTurn();
	OnTurnChanged.Broadcast(nullptr, nullptr, GameStateInstance->GetTurnCount());
}

