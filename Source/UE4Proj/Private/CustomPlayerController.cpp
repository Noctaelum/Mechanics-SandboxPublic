// Fill out your copyright notice in the Description page of Project Settings.

#include "CustomPlayerController.h"
#include "CustomFPCharacter.h"

void ACustomPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//Bind our actions and mappings
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACustomPlayerController::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACustomPlayerController::StopJumping);
	InputComponent->BindAxis("LookUp", this, &ACustomPlayerController::LookUp);
	InputComponent->BindAxis("MoveForward", this, &ACustomPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ACustomPlayerController::MoveRight);
	InputComponent->BindAxis("Turn", this, &ACustomPlayerController::Turn);
}

void ACustomPlayerController::Jump()
{
	if (GetCharacter())
	{
		GetCharacter()->Jump();
	}
}

void ACustomPlayerController::StopJumping()
{
	if (GetCharacter())
	{
		GetCharacter()->StopJumping();
	}
}

void ACustomPlayerController::LookUp(float AxisValue)
{
	if (GetPawn())
	{
		ACustomFPCharacter* PossessedPawn = Cast<ACustomFPCharacter>(GetPawn());
		if (PossessedPawn)
		{
			PossessedPawn->LookUp(AxisValue);
		}
	}
}

void ACustomPlayerController::MoveForward(float AxisValue)
{
	if (GetPawn())
	{
		ACustomFPCharacter* PossessedPawn = Cast<ACustomFPCharacter>(GetPawn());
		if (PossessedPawn)
		{
			PossessedPawn->MoveForward(AxisValue);
		}
	}
}

void ACustomPlayerController::MoveRight(float AxisValue)
{
	if (GetPawn())
	{
		ACustomFPCharacter* PossessedPawn = Cast<ACustomFPCharacter>(GetPawn());
		if (PossessedPawn)
		{
			PossessedPawn->MoveRight(AxisValue);
		}
	}
}

void ACustomPlayerController::Turn(float AxisValue)
{
	if (GetPawn())
	{
		ACustomFPCharacter* PossessedPawn = Cast<ACustomFPCharacter>(GetPawn());
			if (PossessedPawn)
			{
				PossessedPawn->Turn(AxisValue);
			}
	}
}
