// Fill out your copyright notice in the Description page of Project Settings.


#include "DAction.h"

bool UDAction::StartAction_Implementation()
{
	GEngine->AddOnScreenDebugMessage(0, 1, FColor::Blue, "Action Started");
	return true;
}

bool UDAction::StopAction_Implementation()
{
	GEngine->AddOnScreenDebugMessage(0, 1, FColor::Red, "Action Stopped");
	return true;
}

bool UDAction::IsRunning()
{
	return bIsRunning;
}
