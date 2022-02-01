// Copyright Epic Games, Inc. All Rights Reserved.


#include "UnrealCGActualActualGameModeBase.h"
#include "MyWorldSubsystem.h"


void AUnrealCGActualActualGameModeBase::StartPlay()
{
	Super::StartPlay();

	UMyWorldSubsystem* OWSS = GetWorld()->GetSubsystem<UMyWorldSubsystem>();

	if (OWSS)
	{
		OWSS->CreateObjectiveWidgets();
		OWSS->DisplayObjectiveWidget();
		//OWSS->DisplayObjectiveCompleteWidget();
	}

}
