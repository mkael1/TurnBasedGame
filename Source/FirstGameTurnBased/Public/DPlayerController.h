// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FIRSTGAMETURNBASED_API ADPlayerController : public APlayerController
{
	GENERATED_BODY()


protected:
	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UUserWidget> CombatWidgetClass;

	UPROPERTY()
	UUserWidget* CombatWidgetInstance;

	UFUNCTION(BlueprintCallable)
	void ToggleCombatUI();
	
};
