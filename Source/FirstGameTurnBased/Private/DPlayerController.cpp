// Fill out your copyright notice in the Description page of Project Settings.


#include "DPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "DCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "DGameModeBase.h"
#include "DAction.h"
#include "DAttributeComponent.h"


void ADPlayerController::BeginPlay()
{
	Super::BeginPlay();

	InitializePlayerParty();
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	SetInputMode(FInputModeGameAndUI());
}

void ADPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	GEngine->AddOnScreenDebugMessage(0, 0, FColor::White, "Selected Actor: " + GetNameSafe(SelectedActor));
	GEngine->AddOnScreenDebugMessage(2, 0, FColor::Blue, "Action: " + GetNameSafe(SelectedAction));
	GEngine->AddOnScreenDebugMessage(1, 0, FColor::Red, "Energy: " + FString::FromInt(ActivePartyMemberEnergy));


	if (SelectedAction)
	{
		FHitResult Hit;

		GetHitResultUnderCursorForObjects(ObjectQueryParam, true, Hit);
		if (!Hit.GetActor())
		{
			SelectedActor = nullptr;
			return;
		}
		SelectedActor = Hit.GetActor();
	}
}

void ADPlayerController::InitializePlayerParty()
{
	ADGameModeBase* MyMode = Cast<ADGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	AActor* PlayerStartActor = MyMode->FindPlayerStart(this);

	ADCharacter* InitialPartyMember = AddCharacterToParty(StartingPartyMember, PlayerStartActor);
	Possess(InitialPartyMember);
	SetPartyLeader(InitialPartyMember);
}

ADCharacter* ADPlayerController::AddCharacterToParty(TSubclassOf<ADCharacter> CharacterClass, AActor* PlayerStartActor = nullptr)
{
	if (PartyMembers.Num() >= MaxPartySize)
	{
		UE_LOG(LogTemp, Warning, TEXT("Trying to add a party member when you already reached the limit."));
		return nullptr;
	}

	if (!PlayerStartActor && !PartyLeader)
	{
		UE_LOG(LogTemp, Warning, TEXT("Trying to spawn a party member without a leader or a starting location."));
		return nullptr;
	}

	FVector StartingLocation;
	FRotator StartingRotation;

	// Priority is for the actor passed in and if no actor take party leader position to spawn
	if (PlayerStartActor != nullptr)
	{
		StartingLocation = PlayerStartActor->GetActorLocation();
		StartingRotation = PlayerStartActor->GetActorRotation();
	}
	else
	{
		StartingLocation = PartyLeader->GetActorLocation();
		StartingRotation = PartyLeader->GetActorRotation();
	}

	ADCharacter* PartyCharacter = Cast<ADCharacter>(GetWorld()->SpawnActor<AActor>(CharacterClass, StartingLocation, StartingRotation));

	PartyMembers.Push(PartyCharacter);
	return PartyCharacter;
}

void ADPlayerController::SetPartyLeader(ADCharacter* PartyMemberToSetLeader)
{
	for (ADCharacter* PartyMember : PartyMembers)
	{
		if (PartyMember == PartyMemberToSetLeader)
		{
			PartyLeader = PartyMemberToSetLeader;
		}
	}
}

ADCharacter* ADPlayerController::GetPartyLeader()
{
	return PartyLeader;
}


void ADPlayerController::SetActivePartyMember(AActor* PartyMemberToSetActive)
{
	ADCharacter* PartyMemberCharacter = Cast<ADCharacter>(PartyMemberToSetActive);
	if (!PartyMemberCharacter)
	{
		GEngine->AddOnScreenDebugMessage(0, 1, FColor::Red, "Not a character");
		return;
	}

	for (ADCharacter* PartyMember : PartyMembers)
	{
		if (PartyMember == PartyMemberToSetActive)
		{
			ActivePartyMember = PartyMemberCharacter;
			UDAttributeComponent* AttributeComp = Cast<UDAttributeComponent>(PartyMemberCharacter->GetComponentByClass(UDAttributeComponent::StaticClass()));
			ActivePartyMemberEnergy = AttributeComp->GetEnergMax();
		}
	}
}

ADCharacter* ADPlayerController::GetActivePartyMember()
{
	return ActivePartyMember;
}

bool ADPlayerController::SelectAction(UDAction* Action)
{
	if (!Action)
	{
		return false;
	}

	int EnergyCost = Action->GetEnergyCost();
	if (ActivePartyMemberEnergy >= EnergyCost)
	{
		SelectedAction = Action;
		return true;
	}

	return false;
}

void ADPlayerController::PrimaryInteract()
{
	GEngine->AddOnScreenDebugMessage(0, 1, FColor::White, "Test");
	if (ActivePartyMember && SelectedActor && ActivePartyMemberEnergy >= SelectedAction->GetEnergyCost())
	{
		int EnergyCost = SelectedAction->GetEnergyCost();
		ActivePartyMemberEnergy -= EnergyCost;
		ActivePartyMember->UseCombatAction(SelectedActor, SelectedAction);
		OnActionUsed.Broadcast(ActivePartyMember, ActivePartyMemberEnergy);
	}
}

void ADPlayerController::ToggleCombatUI()
{
	if (!ensure(CombatWidgetClass))
	{
		return;
	}

	if (CombatWidgetInstance && CombatWidgetInstance->IsInViewport())
	{
		CombatWidgetInstance->RemoveFromParent();
		CombatWidgetInstance = nullptr;
		bShowMouseCursor = false;
		SetInputMode(FInputModeGameOnly());
	}

	CombatWidgetInstance = CreateWidget<UUserWidget>(this, CombatWidgetClass);
	if (CombatWidgetInstance)
	{
		CombatWidgetInstance->AddToViewport(10);
		bShowMouseCursor = true;
		SetInputMode(FInputModeGameAndUI());
	}
}



void ADPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &ADPlayerController::PrimaryInteract);
}
