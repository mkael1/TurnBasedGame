// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "DAICharacter.generated.h"

class USphereComponent;
class UDInteractionComponent;
class UDActionComponent;
class UDWorldUserWidget;
class UDAttributeComponent;
class UUserWidget;
/**
 * 
 */
UCLASS()
class FIRSTGAMETURNBASED_API ADAICharacter : public APaperZDCharacter
{
	GENERATED_BODY()

public:
	ADAICharacter();

	virtual void PostInitializeComponents() override;

protected:
	UPROPERTY()
		UDWorldUserWidget* HealthBarWidgetInstance;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
		TSubclassOf<UUserWidget> HealthBarWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UDAttributeComponent* AttributeComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UDActionComponent* ActionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UDInteractionComponent* InteractionComp;

	UFUNCTION(BlueprintCallable)
		void HandleDeath(AActor* InstigatorActor, AActor* Victim);

	UFUNCTION(BlueprintCallable)
	void HandleCombatEnded(AActor* Winner);

	virtual void BeginPlay() override;
	
};
