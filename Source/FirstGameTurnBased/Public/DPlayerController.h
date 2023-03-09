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

	virtual void SetupInputComponent() override;

	UFUNCTION(BlueprintCallable, Category = "Party")
		ADCharacter* AddCharacterToParty(TSubclassOf<ADCharacter> CharacterToAdd, AActor* PlayerStartActor);

	UFUNCTION(BlueprintCallable, Category = "Party")
		void SetPartyLeader(ADCharacter* PartyMemberToSetLeader);

	UFUNCTION(BlueprintCallable, Category = "Party")
		ADCharacter* GetPartyLeader();

	UFUNCTION(BlueprintCallable, Category = "Combat")
	bool SelectAction(TSubclassOf<UDAction> Action);

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void SetActivePartyMember(AActor* PartyMemberToSetActive);

protected:
	// Object types to query on tick when an ability is selected.
	UPROPERTY(EditDefaultsOnly, Category = "UI")
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectQueryParam;

	UPROPERTY()
		ADCharacter* ActivePartyMember;

	UPROPERTY()
		int ActivePartyMemberEnergy;

	UPROPERTY()
		TSubclassOf<UDAction> SelectedAction;

	UPROPERTY()
	TSubclassOf<APawn> SelectedPawn;

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

	UPROPERTY()
	AActor* SelectedActor;




	UFUNCTION(BlueprintCallable)
		void ToggleCombatUI();

	UFUNCTION(BlueprintCallable)
	void PrimaryInteract();

	virtual void BeginPlay() override;

	void InitializePlayerParty();


	virtual void Tick(float DeltaSeconds) override;
};
