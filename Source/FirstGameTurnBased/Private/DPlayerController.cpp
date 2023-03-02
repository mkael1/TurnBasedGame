// Fill out your copyright notice in the Description page of Project Settings.


#include "DPlayerController.h"
#include "Blueprint/UserWidget.h"

void ADPlayerController::ToggleCombatUI()
{
	if (!ensure(CombatWidgetClass)) {
		return;
	}

	if (CombatWidgetInstance && CombatWidgetInstance->IsInViewport()) {
		CombatWidgetInstance->RemoveFromParent();
		CombatWidgetInstance = nullptr;
		bShowMouseCursor = false;
		SetInputMode(FInputModeGameOnly());
	}

	CombatWidgetInstance = CreateWidget<UUserWidget>(this, CombatWidgetClass);
	if (CombatWidgetInstance) {
		CombatWidgetInstance->AddToViewport(10);
		bShowMouseCursor = true;
		SetInputMode(FInputModeUIOnly());
	}
}
