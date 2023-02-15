// Fill out your copyright notice in the Description page of Project Settings.


#include "DGameModeBase.h"

void ADGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	EnterCombat();
}

void ADGameModeBase::EnterCombat()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
}



