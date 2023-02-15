// Fill out your copyright notice in the Description page of Project Settings.


#include "DCharacter.h"

#include "DAction.h"
#include "DActionComponent.h"
#include "DAttributeComponent.h"
#include "DWorldUserWidget.h"
#include "DAction.h"

ADCharacter::ADCharacter()
{
	AttributeComp = CreateDefaultSubobject<UDAttributeComponent>("AttributeComp");
	ActionComp = CreateDefaultSubobject<UDActionComponent>("ActionComp");
}

void ADCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();



	if (HealthBarWidgetInstance == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(0, 0, FColor::White, "Test");
		HealthBarWidgetInstance = CreateWidget<UDWorldUserWidget>(GetWorld(), HealthBarWidgetClass);
		HealthBarWidgetInstance->AttachedActor = this;
		HealthBarWidgetInstance->AddToViewport();
	}
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

void ADCharacter::PrimaryAttack()
{
	ActionComp->StartActionByName("PrimaryAttack");
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

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ADCharacter::PrimaryAttack);
}