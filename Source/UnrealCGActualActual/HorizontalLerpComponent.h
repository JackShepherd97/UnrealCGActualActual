// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HorizontalLerpComponent.generated.h"

UENUM()
enum class EHorizLerpState
{
	LS_Start,
	LS_Moving,
	LS_End,
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALCGACTUALACTUAL_API UHorizontalLerpComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	EHorizLerpState LerpState;

public:	
	// Sets default values for this component's properties
	UHorizontalLerpComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FVector StartLocation = FVector::ZeroVector;
	FVector DesiredLocation = FVector::ZeroVector;
	FVector FinalLocation = FVector::ZeroVector;

	UPROPERTY(EditAnywhere)
	float TimeToLerp = 5.f;
	float CurrentLerpTime = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FirstVectorLerp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SecondVectorLerp;
		
};
