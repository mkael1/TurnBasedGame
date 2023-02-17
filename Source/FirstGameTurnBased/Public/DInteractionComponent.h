// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DInteractionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIRSTGAMETURNBASED_API UDInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDInteractionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	FCollisionShape CollisionSphere;

	UPROPERTY(EditDefaultsOnly, Category="Collision")
	float CollisionMaxRange;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
