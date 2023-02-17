// Fill out your copyright notice in the Description page of Project Settings.


#include "DInteractionComponent.h"

#include "DGameplayInterface.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UDInteractionComponent::UDInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UDInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	CollisionSphere = FCollisionShape::MakeSphere(CollisionMaxRange);

}


// Called every frame
void UDInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	// draw collision sphere
	DrawDebugSphere(GetWorld(), GetOwner()->GetActorLocation(), CollisionSphere.GetSphereRadius(), 50, FColor::Red, false);
	FCollisionObjectQueryParams Params;
	Params.AddObjectTypesToQuery(ECC_WorldDynamic);
	
	TArray<FHitResult> Hits;
	GetWorld()->SweepMultiByObjectType(Hits, GetOwner()->GetActorLocation(), GetOwner()->GetActorLocation(), FQuat::Identity, Params, CollisionSphere);


	for (FHitResult Hit : Hits)
	{
		AActor* ActorHit = Hit.GetActor();
		if (ActorHit->Implements<UDGameplayInterface>())
		{
			GEngine->AddOnScreenDebugMessage(0, 1, FColor::Red, "Test");
		}
	}
}

