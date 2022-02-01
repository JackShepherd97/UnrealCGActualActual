// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveHUD.h"
#include "Components/TextBlock.h"

void UObjectiveHUD::UpdateObjectivesCompleted(int32 ObjectivesCompleted, int32 TotalObjectives)
{
	if (ObjectivesText)
	{
		ObjectivesText->SetText(FText::Format(FTextFormat::FromString("{0} / {1}"), ObjectivesCompleted, TotalObjectives));
	}
}
