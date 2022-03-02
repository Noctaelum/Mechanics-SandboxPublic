// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Character.h"
#include "CPP_CharacterController.generated.h"

UCLASS()
class UE4PROJ_API ACPP_CharacterController : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACPP_CharacterController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	void HorizontalMove(float value);
	void VerticalMove(float value);

	void HorizontalRotation(float value);
	void VerticalRotation(float value);

	void Switch();

	UPROPERTY()
	UCameraComponent* CameraComponent;

	UPROPERTY()
	USpringArmComponent* ArmComponent;

	UPROPERTY()
	bool firstPerson;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* PlayerMesh;
};
