// Fill out your copyright notice in the Description page of Project Settings.


#include "DAttributeComponent.h"
#include "DGameModeBase.h"

// Sets default values for this component's properties
UDAttributeComponent::UDAttributeComponent()
{
	HealthMax = 100;
	Health = 100;
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
		if (Amount < 0 && NewHealth <= 0)
		{
			ADGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ADGameModeBase>();
			if (GameMode)
			{
				OnDeathEvent.Broadcast(Instigator, GetOwner());
			}
		}
		return true;
	}

	return false;
}

int UDAttributeComponent::GetEnergMax()
{
	return EnergyMax;
}

