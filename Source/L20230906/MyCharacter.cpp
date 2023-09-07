// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubSystems.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetRelativeLocationAndRotation(
		FVector(0.f, 0.f, -GetCapsuleComponent()->GetScaledCapsuleHalfHeight()),
		FRotator(0.f, -90.f, 0.f));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (PC)
	{
		UEnhancedInputLocalPlayerSubsystem* LocalPlayerSystem
			= ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());

		if (LocalPlayerSystem && DefaultMappingContext)
		{
			LocalPlayerSystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EIC)
	{
		EIC->BindAction(IA_MoveForwardAndRight, ETriggerEvent::Triggered, this, &AMyCharacter::Move);
		EIC->BindAction(IA_Look, ETriggerEvent::Triggered, this, &AMyCharacter::Look);
		EIC->BindAction(IA_Crouch, ETriggerEvent::Triggered, this, &AMyCharacter::DoCrouch);
	}



}

void AMyCharacter::Move(const FInputActionValue& Value)
{
	FVector2D Vector = Value.Get<FVector2D>();

	FRotator CameraRotation = GetControlRotation();
	FRotator XZPlaneRotation = FRotator(0, CameraRotation.Yaw, 0);

	//XZPlaneRotation.Vector()
	FVector ForwardVector = UKismetMathLibrary::GetForwardVector(XZPlaneRotation);
	FVector RightVector = UKismetMathLibrary::GetRightVector(XZPlaneRotation);

	AddMovementInput(ForwardVector, Vector.Y);
	AddMovementInput(RightVector, Vector.X);
}

void AMyCharacter::Look(const FInputActionValue& Value)
{
	FVector2D Vector = Value.Get<FVector2D>();

	

	AddControllerPitchInput(Vector.Y);
	AddControllerYawInput(Vector.X);
}

void AMyCharacter::DoCrouch(const FInputActionValue& Value)
{
	if (CanCrouch())
	{
		Crouch();
	}
	else
	{
		UnCrouch();
	}

}

