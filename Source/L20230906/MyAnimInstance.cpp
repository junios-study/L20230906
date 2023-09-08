// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "MyCharacter.h"
#include "Gameframework/CharacterMovementComponent.h"
#include "KismetAnimationLibrary.h"

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	AMyCharacter* Pawn = Cast<AMyCharacter>(TryGetPawnOwner());
	if (Pawn)
	{
		//Update Pawn Data 
		Speed = Pawn->GetCharacterMovement()->Velocity.Size();

		Direction = UKismetAnimationLibrary::CalculateDirection(Pawn->GetCharacterMovement()->Velocity,
			Pawn->GetActorRotation());

		//Pawn->GetCharacterMovement()->IsCrouching()
		bIsCrouch = Pawn->bIsCrouched;

		AimYaw = Pawn->GetBaseAimRotation().Yaw;
		AimPitch = Pawn->GetBaseAimRotation().Pitch;
	}

}
