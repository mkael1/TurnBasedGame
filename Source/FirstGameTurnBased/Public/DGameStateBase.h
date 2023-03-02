// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "DGameStateBase.generated.h"

class ADCharacter;
/**
 *
 */
UCLASS()
class FIRSTGAMETURNBASED_API ADGameState : public AGameStateBase
{
	GENERATED_BODY()

protected:

	APawn* TeamOne;

	APawn* TeamTwo;

	APawn* CurrentTurn;

	UPROPERTY(BlueprintReadWrite)
	int TurnCount;


public:

	UFUNCTION(BlueprintCallable)
		void SetTeamOne(APawn* Characters);

	UFUNCTION(BlueprintCallable)
		void SetTeamTwo(APawn* Enemies);

	UFUNCTION(BlueprintCallable)
		APawn* GetTeamOne();

	UFUNCTION(BlueprintCallable)
		APawn* GetTeamTwo();

	UFUNCTION(BlueprintCallable)
		APawn* GetCurrentTurn();

	UFUNCTION(BlueprintCallable)
		void ChangeTurn();

	UFUNCTION(BlueprintCallable)
	int GetTurnCount();



};
