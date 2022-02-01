// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDoorOpen);

class UDoorInteractionComponent;

UCLASS()
class UNREALCGACTUALACTUAL_API AInteractableDoor : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* DoorMesh;

	UDoorInteractionComponent* DoorInteractionComponent;
	
public:	
	// Sets default values for this actor's properties
	AInteractableDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FOnDoorOpen OnDoorOpen;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void InteractionSuccess();

	UFUNCTION()
	void DoorOpen();
};
