// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class L20230906_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State")
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State")
	float Direction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State")
	float AimYaw;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State")
	float AimPitch;
};
