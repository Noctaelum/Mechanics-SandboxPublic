// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Character.h"
#include "CustomPlayerController.generated.h"


UCLASS()
class UE4PROJ_API ACustomPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
	virtual void SetupInputComponent() override;

public:
	void Jump();
	void StopJumping();
	void LookUp(float AxisValue);
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void Turn(float AxisValue);
};
