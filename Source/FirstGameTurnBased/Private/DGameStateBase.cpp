// Fill out your copyright notice in the Description page of Project Settings.


#include "DGameStateBase.h"

void ADGameState::SetTeamOne(APawn* Characters)
{
	TeamOne = Characters;
}

void ADGameState::SetTeamTwo(APawn* Enemies)
{
	TeamTwo = Enemies;
}

APawn* ADGameState::GetTeamOne()
{
	return TeamOne;
}

APawn* ADGameState::GetTeamTwo()
{
	return TeamTwo;
}

APawn* ADGameState::GetCurrentTurn()
{
	return CurrentTurn;
}

void ADGameState::ChangeTurn()
{
	if (CurrentTurn == nullptr || CurrentTurn == TeamTwo)
	{
		CurrentTurn = TeamOne;
	}
	else
	{
		CurrentTurn = TeamTwo;
	}

	TurnCount++;
}

int ADGameState::GetTurnCount()
{
	return TurnCount;
}

EGameStatus ADGameState::GetGameStatus()
{
	return GameStatus;
}

void ADGameState::SetGameStatus(EGameStatus NewStatus)
{
	GameStatus = NewStatus;
}


