// Fill out your copyright notice in the Description page of Project Settings.


#include "DAttributeComponent.h"

// Sets default values for this component's properties
UDAttributeComponent::UDAttributeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	HealthMax = 100;
	Health = 100;
}


// Called every frame
void UDAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

float UDAttributeComponent::GetHealthMax()
{
	return HealthMax;
}

float UDAttributeComponent::GetHealth()
{
	return Health;
}

bool UDAttributeComponent::ApplyHealthChange(AActor* Instigator, const float Amount)
{
	float NewHealth = Health + Amount;
	float OldHealth = Health;

	Health = FMath::Clamp(NewHealth, 0, HealthMax);

	if (NewHealth != OldHealth)
	{
		OnHealthChanged.Broadcast(Instigator, this, Amount - Health, Health);
		return true;
	}

	return false;
}
