// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DAction.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class FIRSTGAMETURNBASED_API UDAction : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent)
	bool StartAction();

	UFUNCTION(BlueprintNativeEvent)
	bool StopAction();

	bool IsRunning();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Action")
	FName ActionName;

private:


	bool bIsRunning;

};
