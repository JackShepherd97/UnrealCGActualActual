// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyPlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UHealthComponent;

UCLASS()
class UNREALCGACTUALACTUAL_API AMyPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UHealthComponent* HealthComponent;

	APlayerController* PlayerController;

	float MouseTurnRate = 1.0f;
	float MouseLookUpRate = 1.0f;

	int JumpCount = 0;

	float DefaultGravityScale;

public:
	// Sets default values for this character's properties
	AMyPlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MouseTurn(float Value);

	void MouseLook(float Value);

	void MoveForward(float Value);

	void MoveRight(float Value);

	void OnDeath();

	virtual void FellOutOfWorld(const class UDamageType& dmgType) override;

	void Jump();

	virtual void Landed(const FHitResult& Hit) override;

	virtual void NotifyJumpApex() override;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;


};
