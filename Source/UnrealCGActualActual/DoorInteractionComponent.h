// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DoorInteractionComponent.generated.h"

class ATriggerBox;


UENUM()
enum class EDoorState
{
	DS_Closed,
	DS_Opening,
	DS_Opened,
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDoorOpen);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALCGACTUALACTUAL_API UDoorInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorInteractionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FRotator StartRotation = FRotator::ZeroRotator;
	FRotator DesiredRotation = FRotator::ZeroRotator;
	FRotator FinalRotation = FRotator::ZeroRotator;

	float CurrentRotationTime = 0;
	float TimeToRotate = 2.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ATriggerBox* DoorTrigger;

	
	UPROPERTY(BlueprintAssignable, Category = "Door Interaction Component")
	FOnDoorOpen DoorOpen;

	UPROPERTY(VisibleAnywhere)
	EDoorState DoorState;
};
