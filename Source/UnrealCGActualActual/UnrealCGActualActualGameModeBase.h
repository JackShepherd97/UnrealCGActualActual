// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UnrealCGActualActualGameModeBase.generated.h"

class UObjectiveHUD;

UCLASS()
class UNREALCGACTUALACTUAL_API AUnrealCGActualActualGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> ObjectiveCompleteWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UObjectiveHUD> ObjectiveWidget;

	
	virtual void StartPlay() override;
};
