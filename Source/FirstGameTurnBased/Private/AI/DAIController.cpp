// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/DAIController.h"

void ADAIController::BeginPlay()
{
	Super::BeginPlay();

	if (ensure(BehaviorTree))
	{
		RunBehaviorTree(BehaviorTree);
	}
}
