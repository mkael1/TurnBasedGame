// Fill out your copyright notice in the Description page of Project Settings.


#include "DAction.h"

#include "DActionComponent.h"

bool UDAction::StartAction_Implementation()
{
	UDActionComponent* Comp = GetActionComp();

	if (BlockedTags.Num() > 0 && Comp->ActiveGameplayTags.HasAny(BlockedTags))
	{
		return false;
	}

	GEngine->AddOnScreenDebugMessage(0, 1, FColor::Blue, "Action Started");
	bIsRunning = true;
	Comp->ActiveGameplayTags.AppendTags(GrantsTag);

	return true;
}

bool UDAction::StopAction_Implementation()
{
	GEngine->AddOnScreenDebugMessage(0, 1, FColor::Red, "Action Stopped");

	bIsRunning = false;
	UDActionComponent* Comp = GetActionComp();
	Comp->ActiveGameplayTags.RemoveTags(GrantsTag);

	return true;
}

bool UDAction::GetIsRunning() const
{
	return bIsRunning;
}

UDActionComponent* UDAction::GetActionComp()
{
	return Cast<UDActionComponent>(GetOuter());
}
