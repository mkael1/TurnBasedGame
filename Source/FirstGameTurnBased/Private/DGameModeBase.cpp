// Fill out your copyright notice in the Description page of Project Settings.


#include "DGameModeBase.h"
#include "DGameStateBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DPlayerController.h"
#include "DAttributeComponent.h"


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
	UDAttributeComponent* AttributeComp = Cast<UDAttributeComponent>(PlayerPawn->GetComponentByClass(UDAttributeComponent::StaticClass()));
	AttributeComp->OnDeathEvent.AddDynamic(this, &ADGameModeBase::OnActorKilled);

	UDAttributeComponent* EnemyAttributeComp = Cast<UDAttributeComponent>(EnemyPawn->GetComponentByClass(UDAttributeComponent::StaticClass()));
	EnemyAttributeComp->OnDeathEvent.AddDynamic(this, &ADGameModeBase::OnActorKilled);


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
	APawn* TeamOne = GameStateInstance->GetTeamOne();
	APawn* TeamTwo = GameStateInstance->GetTeamTwo();

	UDAttributeComponent* AttributeComp = Cast<UDAttributeComponent>(TeamOne->GetComponentByClass(UDAttributeComponent::StaticClass()));
	AttributeComp->OnDeathEvent.RemoveDynamic(this, &ADGameModeBase::OnActorKilled);

	UDAttributeComponent* AttributeComp2 = Cast<UDAttributeComponent>(TeamTwo->GetComponentByClass(UDAttributeComponent::StaticClass()));
	AttributeComp2->OnDeathEvent.RemoveDynamic(this, &ADGameModeBase::OnActorKilled);


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

void ADGameModeBase::OnActorKilled(AActor* InstigatorActor, AActor* Victim)
{
	EndCombat();
}

void ADGameModeBase::DevSwitchTurn()
{
	GameStateInstance->ChangeTurn();
	OnTurnChanged.Broadcast(nullptr, nullptr, GameStateInstance->GetTurnCount());
}

