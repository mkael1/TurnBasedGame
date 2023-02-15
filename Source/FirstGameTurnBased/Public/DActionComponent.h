// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DActionComponent.generated.h"


class UDAction;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIRSTGAMETURNBASED_API UDActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDActionComponent();


	UFUNCTION(BlueprintCallable)
	bool StartActionByName(FName ActionName);

	UFUNCTION(BlueprintCallable)
	void AddAction(TSubclassOf<UDAction> ActionClass);



protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category="Actions")
	TArray<TSubclassOf<UDAction>> DefaultActions;

	UPROPERTY(BlueprintReadOnly)
	TArray<UDAction*> Actions;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
