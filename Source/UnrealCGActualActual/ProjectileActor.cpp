// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileActor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "MyPlayerCharacter.h"

// Sets default values
AProjectileActor::AProjectileActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	StaticMesh->SetupAttachment(RootComponent);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	StaticMesh->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
	

	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Component"));
	CollisionComponent->SetupAttachment(StaticMesh);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	CollisionComponent->OnComponentHit.AddDynamic(this, &AProjectileActor::OnHit);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->InitialSpeed = 3500.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
}	

// Called when the game starts or when spawned
void AProjectileActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectileActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectileActor::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AMyPlayerCharacter* PlayerCharacter = Cast<AMyPlayerCharacter>(OtherActor);

	if (PlayerCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Hit"));
		TSubclassOf<UDamageType> const ValidDamageTypeClass = TSubclassOf<UDamageType>(UDamageType::StaticClass());
		FDamageEvent DamageEvent(ValidDamageTypeClass);
		PlayerCharacter->TakeDamage(100.f, DamageEvent, nullptr, this);
	}

	UE_LOG(LogTemp, Warning, TEXT("Hit"));
	Destroy();
}


