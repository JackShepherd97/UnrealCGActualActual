// Fill out your copyright notice in the Description page of Project Settings.


#include "FiringActor.h"
#include "ProjectileActor.h"
#include "Components/SceneComponent.h"

// Sets default values
AFiringActor::AFiringActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMesh->SetupAttachment(RootComponent);

	ProjectileSpawnLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Location"));
	ProjectileSpawnLocation->SetupAttachment(StaticMesh);


}

// Called when the game starts or when spawned
void AFiringActor::BeginPlay()
{
	Super::BeginPlay();

	
	Fire();
}

// Called every frame
void AFiringActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFiringActor::Fire()
{
	GetWorldTimerManager().ClearTimer(FireHandle);

	FVector SpawnLocation = ProjectileSpawnLocation->GetComponentLocation();
	FRotator SpawnRotation = ProjectileSpawnLocation->GetComponentRotation();
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<AProjectileActor>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);

	GetWorldTimerManager().SetTimer(FireHandle, this, &AFiringActor::Fire, 2.0f);
}


