// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "DCharacter.generated.h"

class UDInteractionComponent;
class UDActionComponent;
class UDWorldUserWidget;
class UDAttributeComponent;
class UUserWidget;
/**
 * 
 */
UCLASS()
class FIRSTGAMETURNBASED_API ADCharacter : public APaperZDCharacter
{
	GENERATED_BODY()

	

public:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	ADCharacter();

	virtual void PostInitializeComponents() override;

	virtual void BeginPlay() override;

	UFUNCTION(Exec)
	void HealSelf(int32 Amount = 100);

	UFUNCTION(BlueprintCallable)
		void UseCombatAction(AActor* Target, TSubclassOf<UDAction> Action);

protected:
	UPROPERTY()
	UDWorldUserWidget* HealthBarWidgetInstance;

	UPROPERTY(EditDefaultsOnly, Category= "UI")
	TSubclassOf<UUserWidget> HealthBarWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UDAttributeComponent* AttributeComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UDActionComponent* ActionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
	UDInteractionComponent* InteractionComp;



	void MoveRight(float Value);
	void MoveUp(float Value);

};

