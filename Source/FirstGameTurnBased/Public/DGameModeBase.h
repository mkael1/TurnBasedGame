// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DGameModeBase.generated.h"


class ADGameState;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnTurnChanged, AActor*, Instigator, AActor*, ActiveActor, int, TurnCount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCombatStarted, AActor*, Player, AActor*, Enemy);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCombatEnded, AActor*, Winner);

/**
 *
 */
UCLASS()
class FIRSTGAMETURNBASED_API ADGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

		virtual void BeginPlay() override;



protected:
	void InitializeTeams(APawn* PlayerPawn, APawn* EnemyPawn);

	void StartCombat();

	void EndCombat();

	UFUNCTION(BlueprintCallable)
		void FinishPlayerCombatTurn(APawn* Player);

	UPROPERTY(BlueprintReadOnly)
		ADGameState* GameStateInstance;

public:

	UFUNCTION(BlueprintCallable)
		void EnterCombat(AActor* Player, AActor* Enemy);

	UPROPERTY(BlueprintAssignable)
		FOnTurnChanged OnTurnChanged;

	UPROPERTY(BlueprintAssignable)
		FOnCombatStarted OnCombatStarted;

	UPROPERTY(BlueprintAssignable)
		FOnCombatEnded OnCombatEnded;

	UFUNCTION()
		virtual void OnActorKilled(AActor* InstigatorActor, AActor* Victim);

	UFUNCTION(BlueprintCallable)
		void DevSwitchTurn();
};
