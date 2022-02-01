// Fill out your copyright notice in the Description page of Project Settings.


#include "MyWorldSubsystem.h"
#include "ObjectiveHUD.h"
#include "UnrealCGActualActualGameModeBase.h"
#include "Kismet/GameplayStatics.h"



void UMyWorldSubsystem::AddObjectives(UObjectiveComponent* ObjComp)
{
	size_t PrevSize = Objectives.Num();
	Objectives.AddUnique(ObjComp);

	if (Objectives.Num() > PrevSize)
	{
		ObjComp->StateChanged.AddUObject(this, &UMyWorldSubsystem::OnObjectiveStateChanged);
	}
}

void UMyWorldSubsystem::OnObjectiveStateChanged(const UObjectiveComponent* ObjComp, EObjectiveState ObjState)
{
	if (Objectives.Num() == 0 || !Objectives.Contains(ObjComp))
	{
		return;
	}

	if (ObjectiveWidget && ObjectiveCompleteWidget)
	{
		if (ObjComp->GetState() == EObjectiveState::OS_Completed && GetCompletedObjectiveCount() == Objectives.Num())
		{
			DisplayObjectiveCompleteWidget();
		}

		

		DisplayObjectiveWidget();
	}

	
}

uint32 UMyWorldSubsystem::GetCompletedObjectiveCount()
{
	uint32 ObjectivesCompleted = 0u;

	for (const UObjectiveComponent* OC : Objectives)
	{
		if (OC && OC->GetState() == EObjectiveState::OS_Completed)
		{
			ObjectivesCompleted++;
		}
	}

	return ObjectivesCompleted;
}

void UMyWorldSubsystem::DisplayObjectiveWidget()
{
	if (ObjectiveWidget)
	{
		if (!ObjectiveWidget->IsInViewport())
		{
			ObjectiveWidget->AddToViewport();
		}

		ObjectiveWidget->UpdateObjectivesCompleted(GetCompletedObjectiveCount(), Objectives.Num());
	}
}

void UMyWorldSubsystem::DisplayObjectiveCompleteWidget()
{
	if (ObjectiveCompleteWidget)
	{
		if (!ObjectiveCompleteWidget->IsInViewport())
		{
			ObjectiveCompleteWidget->AddToViewport();
		}
	}
}

void UMyWorldSubsystem::CreateObjectiveWidgets()
{
	if (ObjectiveWidget == nullptr)
	{
		AUnrealCGActualActualGameModeBase* GM = Cast<AUnrealCGActualActualGameModeBase>(GetWorld()->GetAuthGameMode());
		
		if (GM)
		{
			APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
			ObjectiveWidget = CreateWidget<UObjectiveHUD>(PC, GM->ObjectiveWidget);
			ObjectiveCompleteWidget = CreateWidget<UUserWidget>(PC, GM->ObjectiveCompleteWidget);
		}
	}
}








