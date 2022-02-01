// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "MyPlayerCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"



void UPlayerAnimInstance::NativeInitializeAnimation()
{
	PlayerCharacter = Cast<AMyPlayerCharacter>(TryGetPawnOwner());
}

void UPlayerAnimInstance::UpdateAnimationProperties(float DeltaSeconds)
{
	if (PlayerCharacter == nullptr)
	{
		PlayerCharacter = Cast<AMyPlayerCharacter>(TryGetPawnOwner());

	}

	if (PlayerCharacter)
	{
		FVector Velocity = PlayerCharacter->GetVelocity();
		Velocity.Z = 0;
		Speed = Velocity.Size();

		if (PlayerCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f)
		{
			bIsAccelerating = true;
		}
		else
		{
			bIsAccelerating = false;
		}

		if (PlayerCharacter->GetCharacterMovement()->IsFalling())
		{
			bIsInAir = true;
		}
		else
		{
			bIsInAir = false;
		}

		if (PlayerCharacter->bHasLanded)
		{
			bHasLanded = true;
		}
		else if(PlayerCharacter->bHasLanded == false)
		{
			bHasLanded = false;
		}
		
		FRotator AccRot = UKismetMathLibrary::MakeRotFromX(PlayerCharacter->GetCharacterMovement()->GetCurrentAcceleration());
		FRotator AimRot = PlayerCharacter->GetBaseAimRotation();

		MovementOffsetYaw = UKismetMathLibrary::NormalizedDeltaRotator(AccRot, AimRot).Yaw;
	}
}
