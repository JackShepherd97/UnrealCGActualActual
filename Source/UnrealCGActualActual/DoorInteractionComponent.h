// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.h"
#include "ObjectiveComponent.h"
#include "DoorInteractionComponent.generated.h"

class ATriggerBox;
class UObjectiveComponent;


UENUM()
enum class EDoorState
{
	DS_Closed,
	DS_Opening,
	DS_Opened,
};



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALCGACTUALACTUAL_API UDoorInteractionComponent : public UInteractionComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorInteractionComponent();

	UObjectiveComponent* ObjComp;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;


	FRotator StartRotation = FRotator::ZeroRotator;
	FRotator DesiredRotation = FRotator::ZeroRotator;
	FRotator FinalRotation = FRotator::ZeroRotator;

	float CurrentRotationTime = 0;
	float TimeToRotate = 2.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ATriggerBox* DoorTrigger;

	UPROPERTY(VisibleAnywhere)
	EDoorState DoorState;

	void OnDoorOpen();
};
