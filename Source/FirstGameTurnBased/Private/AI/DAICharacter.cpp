// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/DAICharacter.h"
#include "DAttributeComponent.h"
#include "DActionComponent.h"
#include "DWorldUserWidget.h"
#include "Components/CapsuleComponent.h"
#include "DGameModeBase.h"

ADAICharacter::ADAICharacter()
{
	AttributeComp = CreateDefaultSubobject<UDAttributeComponent>("AttributeComp");
	ActionComp = CreateDefaultSubobject<UDActionComponent>("ActionComp");

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

}

void ADAICharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();


	AttributeComp->OnDeathEvent.AddDynamic(this, &ADAICharacter::HandleDeath);
}

void ADAICharacter::HandleDeath(AActor* InstigatorActor, AActor* Victim)
{
	this->SetActorRotation(FQuat::MakeFromEuler(FVector(0, -90, 0)));
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	HealthBarWidgetInstance->RemoveFromParent();
}

void ADAICharacter::HandleCombatEnded(AActor* Winner)
{
	this->Destroy();
}

void ADAICharacter::BeginPlay()
{
	Super::BeginPlay();

	if (HealthBarWidgetInstance == nullptr && ensure(HealthBarWidgetClass))
	{
		HealthBarWidgetInstance = CreateWidget<UDWorldUserWidget>(GetWorld(), HealthBarWidgetClass);
		HealthBarWidgetInstance->AttachedActor = this;
		HealthBarWidgetInstance->AddToViewport();
	}

	ADGameModeBase* GameMode = Cast<ADGameModeBase>(GetWorld()->GetAuthGameMode());
	GameMode->OnCombatEnded.AddDynamic(this, &ADAICharacter::HandleCombatEnded);
}


