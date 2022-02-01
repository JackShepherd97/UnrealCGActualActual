// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorInteractionComponent.h"
#include "Engine/TriggerBox.h"
#include "MyPlayerCharacter.h"
#include "Components/BoxComponent.h"






// Sets default values for this component's properties
UDoorInteractionComponent::UDoorInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	ObjComp = CreateDefaultSubobject<UObjectiveComponent>(TEXT("Objective Component"));

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &UDoorInteractionComponent::OnOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &UDoorInteractionComponent::OnOverlapEnd);
}


// Called when the game starts
void UDoorInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	StartRotation = GetOwner()->GetActorRotation();
	DesiredRotation = FRotator(0.f, 90.f, 0.f);
	FinalRotation = StartRotation + DesiredRotation;

	DoorState = EDoorState::DS_Closed;
	//ObjComp->SetState(EObjectiveState::OS_Active);
	
}


// Called every frame
void UDoorInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
	if (DoorState == EDoorState::DS_Opening)
	{
		CurrentRotationTime += DeltaTime;
		float RotAlpha = FMath::Clamp(CurrentRotationTime / TimeToRotate, 0.f, 1.0f);
		FRotator NewRotation = FMath::Lerp(StartRotation, FinalRotation, RotAlpha);
		GetOwner()->SetActorRotation(NewRotation);

		if (RotAlpha >= 1.0f)
		{
			OnDoorOpen();
		}
	}


}

void UDoorInteractionComponent::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	AMyPlayerCharacter* PlayerCharacter = Cast<AMyPlayerCharacter>(OtherActor);

	if (PlayerCharacter)
	{
		DoorState = EDoorState::DS_Opening;
		UE_LOG(LogTemp, Warning, TEXT("Player Overlap"));
	}
}


void UDoorInteractionComponent::OnDoorOpen()
{
	CurrentRotationTime = 0;
	DoorState = EDoorState::DS_Opened;
	InteractionSuccess.Broadcast();

	//ObjComp->SetState(EObjectiveState::OS_Completed);
}


