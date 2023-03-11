// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "DAction.generated.h"

class UDActionComponent;
/**
 * 
 */
UCLASS(Blueprintable)
class FIRSTGAMETURNBASED_API UDAction : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent)
	bool StartAction(AActor* Instigator, AActor* Target = nullptr);

	UFUNCTION(BlueprintNativeEvent)
	bool StopAction();

	UFUNCTION(BlueprintCallable)
	bool GetIsRunning() const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Action")
	FName ActionName;

	UFUNCTION(BlueprintCallable)
	int GetEnergyCost();

	UDAction();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Tags")
	FGameplayTagContainer GrantsTag;

	UPROPERTY(EditDefaultsOnly, Category = "Tags")
	FGameplayTagContainer BlockedTags;

	UPROPERTY(EditDefaultsOnly, Category = "Tags")
	FGameplayTagContainer AttributeTags;

	UFUNCTION(BlueprintCallable)
	UDActionComponent* GetActionComp();

	UPROPERTY(EditDefaultsOnly, Category = "Energy")
	int EnergyCost;


	bool bIsRunning;
};
