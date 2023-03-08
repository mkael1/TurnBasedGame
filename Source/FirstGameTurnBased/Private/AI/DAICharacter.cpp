// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/DAICharacter.h"
#include "DAttributeComponent.h"
#include "DActionComponent.h"
#include "DWorldUserWidget.h"

ADAICharacter::ADAICharacter()
{
	AttributeComp = CreateDefaultSubobject<UDAttributeComponent>("AttributeComp");
	ActionComp = CreateDefaultSubobject<UDActionComponent>("ActionComp");

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

}

void ADAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (HealthBarWidgetInstance == nullptr && ensure(HealthBarWidgetClass))
	{
		HealthBarWidgetInstance = CreateWidget<UDWorldUserWidget>(GetWorld(), HealthBarWidgetClass);
		HealthBarWidgetInstance->AttachedActor = this;
		HealthBarWidgetInstance->AddToViewport();
	}
}
