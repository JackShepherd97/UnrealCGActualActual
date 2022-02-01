// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveComponent.h"
#include "MyWorldSubsystem.h"


// Sets default values for this component's properties
UObjectiveComponent::UObjectiveComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;


	// ...
}


// Called when the game starts
void UObjectiveComponent::BeginPlay()
{
	Super::BeginPlay();

	State = EObjectiveState::OS_Active;
	
}

void UObjectiveComponent::InitializeComponent()
{
	Super::InitializeComponent();

	UMyWorldSubsystem* ObjectiveSubsystem = GetWorld()->GetSubsystem<UMyWorldSubsystem>();

	if (ObjectiveSubsystem)
	{
		ObjectiveSubsystem->AddObjectives(this);
	}
}


// Called every frame
void UObjectiveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

