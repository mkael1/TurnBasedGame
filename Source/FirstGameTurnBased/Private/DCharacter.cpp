// Fill out your copyright notice in the Description page of Project Settings.


#include "DCharacter.h"

#include "DActionComponent.h"
#include "DAttributeComponent.h"
#include "DInteractionComponent.h"
#include "DWorldUserWidget.h"
#include "Components/SphereComponent.h"
#include "DAction.h"

ADCharacter::ADCharacter()
{
	AttributeComp = CreateDefaultSubobject<UDAttributeComponent>("AttributeComp");
	ActionComp = CreateDefaultSubobject<UDActionComponent>("ActionComp");
	InteractionComp = CreateDefaultSubobject<UDInteractionComponent>("InteractionComp");
}

void ADCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ADCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ADCharacter::HealSelf(int32 Amount)
{
	AttributeComp->ApplyHealthChange(this, Amount);
}

void ADCharacter::MoveUp(const float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

void ADCharacter::UseCombatAction(AActor* Target, TSubclassOf<UDAction> Action)
{
	FName ActionName = Action.GetDefaultObject()->ActionName;
	ActionComp->StartActionByName(this, ActionName, Target);
}

void ADCharacter::MoveRight(const float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}


void ADCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveRight", this, &ADCharacter::MoveRight);
	PlayerInputComponent->BindAxis("MoveUp", this, &ADCharacter::MoveUp);
}