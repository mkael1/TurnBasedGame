// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DPlayerController.generated.h"

class ADCharacter;
/**
 * 
 */
UCLASS()
class FIRSTGAMETURNBASED_API ADPlayerController : public APlayerController
{
	GENERATED_BODY()


public:

	UFUNCTION(BlueprintCallable)
	void AddCharacterToParty(TSubclassOf<ADCharacter> CharacterToAdd);


protected:

	UPROPERTY(EditDefaultsOnly)
	int MaxPartySize = 4;

	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UUserWidget> CombatWidgetClass;


	// Party members on game start
	UPROPERTY(EditDefaultsOnly, Category="Party")
	TArray<TSubclassOf<ADCharacter>> StartingPartyMembers;

	// Current party members
	UPROPERTY(BlueprintReadOnly)
	TArray<ADCharacter*> PartyMembers;

	UPROPERTY()
	UUserWidget* CombatWidgetInstance;

	UFUNCTION(BlueprintCallable)
	void ToggleCombatUI();

	virtual void BeginPlay() override;
	
};
