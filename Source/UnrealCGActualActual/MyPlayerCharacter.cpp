// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "HealthComponent.h"

// Sets default values
AMyPlayerCharacter::AMyPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->bInheritPitch = true;
	CameraBoom->bInheritYaw = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));

	GetCharacterMovement()->bNotifyApex = true;
}

// Called when the game starts or when spawned
void AMyPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<APlayerController>(GetController());
	
	DefaultGravityScale = GetCharacterMovement()->GravityScale;
}

// Called every frame
void AMyPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMyPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("MouseTurn", this, &AMyPlayerCharacter::MouseTurn);
	PlayerInputComponent->BindAxis("MouseLook", this, &AMyPlayerCharacter::MouseLook);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyPlayerCharacter::Jump);


}

void AMyPlayerCharacter::MouseTurn(float Value)
{
	AddControllerYawInput(MouseTurnRate * Value);
}

void AMyPlayerCharacter::MouseLook(float Value)
{
	AddControllerPitchInput(MouseLookUpRate * Value);
}

void AMyPlayerCharacter::MoveForward(float Value)
{
	if (GetController() != nullptr && Value != 0.f)
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AMyPlayerCharacter::MoveRight(float Value)
{
	if (GetController() != nullptr && Value != 0.f)
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AMyPlayerCharacter::OnDeath()
{
	PlayerController->RestartLevel();
}

void AMyPlayerCharacter::FellOutOfWorld(const class UDamageType& dmgType)
{
	Super::FellOutOfWorld(dmgType);
	
	PlayerController->RestartLevel();
}

void AMyPlayerCharacter::Jump()
{
	if (JumpCount != 2)
	{ 
		GetCharacterMovement()->bNotifyApex = true;
		GetCharacterMovement()->GravityScale = DefaultGravityScale;
		LaunchCharacter(FVector(0, 0, 500.f), false, true);
		JumpCount++;
	}
}

void AMyPlayerCharacter::Landed(const FHitResult& Hit)
{
	JumpCount = 0;

	GetCharacterMovement()->GravityScale = DefaultGravityScale;
	GetCharacterMovement()->bNotifyApex = true;
}

void AMyPlayerCharacter::NotifyJumpApex()
{
	GetCharacterMovement()->GravityScale = 1.5;
	UE_LOG(LogTemp, Warning, TEXT("Apex"));
}

float AMyPlayerCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageAmount = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	if (HealthComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Damage Taken"));
		HealthComponent->TakeDamage(DamageAmount);

		if (HealthComponent->IsDead())
		{
			OnDeath();
		}
	}

	return DamageAmount;
}


