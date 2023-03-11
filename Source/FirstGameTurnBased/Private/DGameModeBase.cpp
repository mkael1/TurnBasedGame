// Fill out your copyright notice in the Description page of Project Settings.


#include "DGameModeBase.h"
#include "DGameStateBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DPlayerController.h"


void ADGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	GameStateInstance = GetGameState<ADGameState>();

}

void ADGameModeBase::EnterCombat(AActor* Player, AActor* Enemy)
{
	OnCombatStarted.Broadcast(Player, Enemy);

	APawn* PlayerPawn = Cast<APawn>(Player);
	APawn* EnemyPawn = Cast<APawn>(Enemy);

	InitializeTeams(PlayerPawn, EnemyPawn);

	StartCombat();
}

void ADGameModeBase::InitializeTeams(APawn* PlayerPawn, APawn* EnemyPawn)
{

	GameStateInstance->SetTeamOne(PlayerPawn);
	GameStateInstance->SetTeamTwo(EnemyPawn);
}

void ADGameModeBase::StartCombat()
{
	GameStateInstance->ChangeTurn();
	GameStateInstance->SetGameStatus(EGameStatus::Combat);
	OnTurnChanged.Broadcast(this, GameStateInstance->GetCurrentTurn(), GameStateInstance->GetTurnCount());
}

void ADGameModeBase::EndCombat()
{
	GameStateInstance->SetGameStatus(EGameStatus::Exploring);
	OnCombatEnded.Broadcast(GameStateInstance->GetTeamOne());
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
		OnTurnChanged.Broadcast(OldActor, GameStateInstance->GetCurrentTurn(), GameStateInstance->GetTurnCount());
	}
}

void ADGameModeBase::OnActorKilled(AActor* VictimActor, AActor* Killer)
{
	VictimActor->SetActorRotation(FQuat::MakeFromEuler(FVector(0, -90, 0)));
	EndCombat();
}

void ADGameModeBase::DevSwitchTurn()
{
	GameStateInstance->ChangeTurn();
	OnTurnChanged.Broadcast(nullptr, nullptr, GameStateInstance->GetTurnCount());
}

