// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LerpComponent.generated.h"

UENUM()
enum class ELerpState
{
	LS_Start,
	LS_Moving, 
	LS_End,
};



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALCGACTUALACTUAL_API ULerpComponent : public UActorComponent
{
	GENERATED_BODY()

	ELerpState LerpState;

public:	
	// Sets default values for this component's properties
	ULerpComponent();

	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FVector StartLocation = FVector::ZeroVector;
	FVector DesiredLocation = FVector::ZeroVector;
	FVector FinalLocation = FVector::ZeroVector;

	float TimeToLerp = 5.f;
	float CurrentLerpTime = 0;
};
