// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomFPCharacter.h"
#include "CPP_Ladder.h"

//Other includes
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

//Other other includes
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Character.h"

// Sets default values
ACustomFPCharacter::ACustomFPCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
}

// Called when the game starts or when spawned
void ACustomFPCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACustomFPCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACustomFPCharacter::LookUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}

void ACustomFPCharacter::MoveForward(float AxisValue)
{
	if (IsOnLadder)
	{
		//Enter Ladder mode
		if (GetCharacterMovement() && CameraComponent)
		{
			GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
			AddMovementInput(CameraComponent->GetForwardVector(), AxisValue);
		}
	}
	else
	{
		AddMovementInput(GetActorForwardVector(), AxisValue);
	}
}

void ACustomFPCharacter::MoveRight(float AxisValue)
{
	if (!IsOnLadder)
	{
		AddMovementInput(GetActorRightVector(), AxisValue);
	}
}

void ACustomFPCharacter::Turn(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}
