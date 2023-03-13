// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DPlayerController.generated.h"

class ADCharacter;
class UDAction;
class UDWorldUserWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnActionUsed, AActor*, Instigator, int, EnergyLeft);
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
		bool SelectAction(UDAction* Action);

	UFUNCTION(BlueprintCallable, Category = "Party")
		void SetActivePartyMember(AActor* PartyMemberToSetActive);

	UFUNCTION(BlueprintCallable, Category = "Party")
	ADCharacter* GetActivePartyMember();

	UPROPERTY(BlueprintAssignable)
		FOnActionUsed OnActionUsed;

protected:
	// Object types to query on tick when an ability is selected.
	UPROPERTY(EditDefaultsOnly, Category = "Trace")
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectQueryParam;

	UPROPERTY()
		ADCharacter* ActivePartyMember;

	UPROPERTY()
		int ActivePartyMemberEnergy;

	UPROPERTY()
		UDAction* SelectedAction;

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

	UPROPERTY()
	UDWorldUserWidget* HoverTargetWidgetInstance;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UDWorldUserWidget> HoverTargetWidgetClass;






	UFUNCTION(BlueprintCallable)
		void ToggleCombatUI();

	UFUNCTION(BlueprintCallable)
		void PrimaryInteract();

	virtual void BeginPlay() override;

	void InitializePlayerParty();


	virtual void Tick(float DeltaSeconds) override;
};
