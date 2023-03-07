// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DPlayerController.generated.h"

class ADCharacter;
class UDAction;
/**
 *
 */
UCLASS()
class FIRSTGAMETURNBASED_API ADPlayerController : public APlayerController
{
	GENERATED_BODY()


public:

	UFUNCTION(BlueprintCallable, Category = "Party")
		ADCharacter* AddCharacterToParty(TSubclassOf<ADCharacter> CharacterToAdd, AActor* PlayerStartActor);

	UFUNCTION(BlueprintCallable, Category = "Party")
		void SetPartyLeader(ADCharacter* PartyMemberToSetLeader);

	UFUNCTION(BlueprintCallable, Category = "Party")
		ADCharacter* GetPartyLeader();

	UFUNCTION(BlueprintCallable, Category = "Action")
	bool SelectAction(TSubclassOf<UDAction> Action);

protected:
	// Object types to query on tick when an ability is selected.
	UPROPERTY(EditDefaultsOnly, Category = "UI")
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectQueryParam;

	UPROPERTY()
		TSubclassOf<UDAction> SelectedAction;

	UPROPERTY(EditDefaultsOnly)
		int MaxPartySize = 4;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
		TSubclassOf<UUserWidget> CombatWidgetClass;

	// Party member on game start
	UPROPERTY(EditDefaultsOnly, Category = "Party")
		TSubclassOf<ADCharacter> StartingPartyMember;

	// Current party members
	UPROPERTY(BlueprintReadOnly)
		TArray<ADCharacter*> PartyMembers;

	UPROPERTY()
		ADCharacter* PartyLeader;

	UPROPERTY()
		UUserWidget* CombatWidgetInstance;


	UFUNCTION(BlueprintCallable)
		void ToggleCombatUI();

	virtual void BeginPlay() override;

	void InitializePlayerParty();


	virtual void Tick(float DeltaSeconds) override;
};
