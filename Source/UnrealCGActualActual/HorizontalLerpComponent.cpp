// Fill out your copyright notice in the Description page of Project Settings.


#include "HorizontalLerpComponent.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values for this component's properties
UHorizontalLerpComponent::UHorizontalLerpComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	FirstVectorLerp = 1000.f;
}


// Called when the game starts
void UHorizontalLerpComponent::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetOwner()->GetActorLocation();
	DesiredLocation = FVector(FirstVectorLerp, 0.f, 0.f);
	FinalLocation = StartLocation + DesiredLocation;

	LerpState = EHorizLerpState::LS_Start;
	
}


// Called every frame
void UHorizontalLerpComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (LerpState == EHorizLerpState::LS_Start)
	{
		CurrentLerpTime += DeltaTime;
		float LerpAlpha = FMath::Clamp(CurrentLerpTime / TimeToLerp, 0.f, 1.0f);
		FVector NewLocation = UKismetMathLibrary::VLerp(StartLocation, FinalLocation, LerpAlpha);
		GetOwner()->SetActorLocation(NewLocation);

		if (LerpAlpha >= 1.0f)
		{
			LerpState = EHorizLerpState::LS_End;
			CurrentLerpTime = 0;
		}
	}
	else if (LerpState == EHorizLerpState::LS_End)
	{
		CurrentLerpTime += DeltaTime;
		float LerpAlpha = FMath::Clamp(CurrentLerpTime / TimeToLerp, 0.f, 1.0f);
		FVector NewLocation = UKismetMathLibrary::VLerp(FinalLocation, StartLocation, LerpAlpha);
		GetOwner()->SetActorLocation(NewLocation);

		if (LerpAlpha >= 1.0f)
		{
			LerpState = EHorizLerpState::LS_Start;
			CurrentLerpTime = 0;
		}
	}
}

