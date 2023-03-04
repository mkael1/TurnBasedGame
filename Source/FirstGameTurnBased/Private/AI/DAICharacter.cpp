// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/DAICharacter.h"
#include "DAttributeComponent.h"
#include "DActionComponent.h"

ADAICharacter::ADAICharacter()
{
	AttributeComp = CreateDefaultSubobject<UDAttributeComponent>("AttributeComp");
	ActionComp = CreateDefaultSubobject<UDActionComponent>("ActionComp");

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}
