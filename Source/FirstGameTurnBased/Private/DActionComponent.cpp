// Fill out your copyright notice in the Description page of Project Settings.


#include "DActionComponent.h"

#include "DAction.h"

// Sets default values for this component's properties
UDActionComponent::UDActionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}
// Called when the game starts
void UDActionComponent::BeginPlay()
{
	Super::BeginPlay();

	for (TSubclassOf<UDAction> ActionClass : DefaultActions)
	{
		AddAction(ActionClass);
	}
}

bool UDActionComponent::StartActionByName(AActor* Instigator, FName ActionName, AActor* TargetActor)
{
	for (UDAction* Action : Actions)
	{
		if (Action && Action->ActionName == ActionName)
		{
			 Action->StartAction(Instigator, TargetActor);
		}
	}
	return false;
}

bool UDActionComponent::StopActionByName(AActor* Instigator, FName ActionName)
{
	for (UDAction* Action : Actions)
	{
		if (Action && Action->ActionName == ActionName)
		{
			return Action->StopAction();
		}
	}
	return false;
}

void UDActionComponent::AddAction(TSubclassOf<UDAction> ActionClass)
{
	if (!ensure(ActionClass))
	{
		return;
	}

	UDAction* NewAction = NewObject<UDAction>(this, ActionClass);
	Actions.Add(NewAction);
}





// Called every frame
void UDActionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

