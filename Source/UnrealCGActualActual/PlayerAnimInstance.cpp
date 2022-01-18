// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "MyPlayerCharacter.h"
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
		Speed = PlayerCharacter->GetVelocity().Size();

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
		
	}
}
