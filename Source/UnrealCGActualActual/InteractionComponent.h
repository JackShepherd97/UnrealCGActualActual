// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDoorInteraction);

class UBoxComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREALCGACTUALACTUAL_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractionComponent();

	FOnDoorInteraction InteractionSuccess;

	UPROPERTY(EditAnywhere)
	UBoxComponent* TriggerBox;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {};

	UFUNCTION()
	virtual void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {};

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void OnInteractionSuccess();

	UBoxComponent* GetTriggerBox() { return TriggerBox; }
};
