// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObjectiveComponent.generated.h"

class UObjectiveComponent;


UENUM()
enum class EObjectiveState
{
	OS_Inactive,
	OS_Active,
	OS_Completed,
};

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnObjectiveStateChanged, const UObjectiveComponent*, EObjectiveState);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALCGACTUALACTUAL_API UObjectiveComponent : public UActorComponent
{
	GENERATED_BODY()

	EObjectiveState State;

	FString Description;

public:	
	// Sets default values for this component's properties
	UObjectiveComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	



	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void InitializeComponent() override;

	void SetState(EObjectiveState NewState);

	EObjectiveState GetState() const { return State; }

	FString GetDescription()  const { return Description; }

	FOnObjectiveStateChanged StateChanged;

private:

	
};
