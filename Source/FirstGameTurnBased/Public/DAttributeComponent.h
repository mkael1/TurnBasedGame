// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DAttributeComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnAttributeChange, AActor*, Instigator, UDAttributeComponent*, OwnerComp, float, Delta, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDeath, AActor*, Instigator, AActor*, Victim);



UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class FIRSTGAMETURNBASED_API UDAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDAttributeComponent();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
		float HealthMax;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
		float Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
		int EnergyMax;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
		int Strength;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
		int Dexterity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attributes")
		int Intellect;

public:

	UFUNCTION(BlueprintCallable)
		float GetHealthMax();

	UFUNCTION(BlueprintCallable)
		float GetHealth();

	UFUNCTION(BlueprintCallable)
		bool ApplyHealthChange(AActor* Instigator, const float Amount);

	UFUNCTION(BlueprintCallable)
		int GetEnergMax();

	UPROPERTY(BlueprintAssignable, Category = "Attributes")
		FOnAttributeChange OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = "Death")
		FOnDeath OnDeathEvent;
};
