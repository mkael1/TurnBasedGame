// Fill out your copyright notice in the Description page of Project Settings.


#include "DCharacter.h"

#include "DActionComponent.h"
#include "DAttributeComponent.h"
#include "DInteractionComponent.h"
#include "DWorldUserWidget.h"
#include "Components/SphereComponent.h"
#include "DAction.h"
#include "Camera/CameraComponent.h"
#include "GameFrameWork/SpringArmComponent.h"

ADCharacter::ADCharacter()
{
	AttributeComp = CreateDefaultSubobject<UDAttributeComponent>("AttributeComp");
	ActionComp = CreateDefaultSubobject<UDActionComponent>("ActionComp");
	InteractionComp = CreateDefaultSubobject<UDInteractionComponent>("InteractionComp");

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);
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

void ADCharacter::UseCombatAction(AActor* Target, UDAction* Action)
{
	FName ActionName = Action->ActionName;
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