// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ObjectiveComponent.h"
#include "MyWorldSubsystem.generated.h"

class UObjectiveComponent;
class UObjectiveHUD;


UCLASS()
class UNREALCGACTUALACTUAL_API UMyWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

	UPROPERTY()
	UObjectiveHUD* ObjectiveWidget;

	UPROPERTY()
	UUserWidget* ObjectiveCompleteWidget;

public:

	TArray<const UObjectiveComponent*> Objectives;

	void AddObjectives(UObjectiveComponent* ObjComp);

	void CreateObjectiveWidgets();

	FString GetCurrentObjectiveDescription();

	void DisplayObjectiveWidget();

	void DisplayObjectiveCompleteWidget();

	void RemoveObjectiveWidget();

	void RemoveObjectiveCompleteWidget();

	void OnObjectiveStateChanged(const UObjectiveComponent* ObjComp, EObjectiveState ObjState);

	uint32 GetCompletedObjectiveCount();
};
