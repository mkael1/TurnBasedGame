// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DGameModeBase.generated.h"


class ADGameState;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnTurnChanged, AActor*, Instigator, AActor*, ActiveActor, int, TurnCount);

/**
 * 
 */
UCLASS()
class FIRSTGAMETURNBASED_API ADGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

protected:
	void EnterCombat();

	void InitializeTeams(APawn* Player);

	void StartCombat();

	void FinishPlayerCombatTurn(APawn* Player);

	UPROPERTY(BlueprintReadOnly)
	ADGameState* GameStateInstance;

public:


	UPROPERTY(BlueprintAssignable)
		FOnTurnChanged OnTurnChanged;
};
