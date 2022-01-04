// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FiringActor.generated.h"


class AProjectileActor;
class USceneComponent;

UCLASS()
class UNREALCGACTUALACTUAL_API AFiringActor : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnLocation;

	FTimerHandle FireHandle;

public:	
	// Sets default values for this actor's properties
	AFiringActor();

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<AProjectileActor> ProjectileClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Fire();

};
