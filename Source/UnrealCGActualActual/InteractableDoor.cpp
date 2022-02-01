// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableDoor.h"
#include "DoorInteractionComponent.h"
#include "Components/BoxComponent.h"



// Sets default values
AInteractableDoor::AInteractableDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Mesh"));
	DoorMesh->SetupAttachment(RootComponent);

	DoorInteractionComponent = CreateDefaultSubobject<UDoorInteractionComponent>(TEXT("Door Interaction Component"));

	if (DoorInteractionComponent->GetTriggerBox())
	{
		DoorInteractionComponent->GetTriggerBox()->SetupAttachment(DoorMesh);
	}
}

// Called when the game starts or when spawned
void AInteractableDoor::BeginPlay()
{
	Super::BeginPlay();

	if (DoorInteractionComponent)
	{
		DoorInteractionComponent->InteractionSuccess.AddDynamic(this,&AInteractableDoor::DoorOpen);
	}
	
}

// Called every frame
void AInteractableDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractableDoor::DoorOpen()
{
	OnDoorOpen.Broadcast();
}


