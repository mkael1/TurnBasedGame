// Fill out your copyright notice in the Description page of Project Settings.


#include "DWorldUserWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/SizeBox.h"
#include "Kismet/GameplayStatics.h"

void UDWorldUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);


	if (!AttachedActor)
	{
		RemoveFromParent();
	}

	FVector2d ScreenPosition;
	bool bIsOnScreen = UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(GetOwningPlayer(), AttachedActor->GetActorLocation() + WorldOffset, ScreenPosition, false);
	if (!bIsOnScreen)
	{
		return;
	}

	if (!ParentSizeBox)
	{
		return;
	}

	ParentSizeBox->SetRenderTranslation(ScreenPosition);
}
