// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_CharacterController.h"

// Sets default values
ACPP_CharacterController::ACPP_CharacterController()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;														//this will automatically possess to player0

	bUseControllerRotationYaw = false;																	//turned this to false so not using unreals built in 
																										//controller rotation
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	//CameraComponent->AttachTo(RootComponent);

	PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
	PlayerMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	ArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));					
	ArmComponent->AttachTo(RootComponent);																//attach the arm comp to it's root
	ArmComponent->TargetArmLength = 300.f;																//sets the position of the camera to 300.f away 
																										//from the player
	ArmComponent->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));										//reset's the rotation back to -45.f
																										//just incase the rotation was not the same when the player
																										//left it

	CameraComponent->AttachTo(ArmComponent, USpringArmComponent::SocketName);

	firstPerson = false;
}

// Called when the game starts or when spawned
void ACPP_CharacterController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_CharacterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACPP_CharacterController::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAxis("Horizontal", this, &ACPP_CharacterController::HorizontalMove);
	InputComponent->BindAxis("Vertical", this, &ACPP_CharacterController::VerticalMove);

	InputComponent->BindAxis("HorizontalRotation", this, &ACPP_CharacterController::HorizontalRotation);
	InputComponent->BindAxis("VerticalRotation", this, &ACPP_CharacterController::VerticalRotation);

	InputComponent->BindAction("ChangeCamera", IE_Pressed, this, &ACPP_CharacterController::Switch);
}

void ACPP_CharacterController::HorizontalMove(float value)
{
	if (value)
	{
		AddMovementInput(GetActorRightVector(), value);
	}
}

void ACPP_CharacterController::VerticalMove(float value)
{
	if (value)
	{
		AddMovementInput(GetActorForwardVector(), value);
	}
}

void ACPP_CharacterController::HorizontalRotation(float value)
{
	if (value)
	{
		AddActorLocalRotation(FRotator(0, value, 0));
	}
}


void ACPP_CharacterController::VerticalRotation(float value)
{
	if (value)
	{
		float temp = ArmComponent->GetRelativeRotation().Pitch + value;
		if (temp < 25 && temp > -65)
		{
			ArmComponent->AddLocalRotation(FRotator(value, 0, 0));
		}
	}
}

void ACPP_CharacterController::Switch()
{
	if (firstPerson)																//if the player is in first person when they press q
	{
		ArmComponent->TargetArmLength = 300.f;										//set the target arm length to 300 (so away from the player)
		ArmComponent->SetRelativeRotation(FRotator(-45, 0, 0));						//point at a -45 degree angle
		CameraComponent->SetRelativeRotation(FRotator(0, 0, 0));
		CameraComponent->AttachTo(ArmComponent, USpringArmComponent::SocketName);
		firstPerson = false;
	}
	else
	{
		CameraComponent->AttachTo(RootComponent);									//if they're not then set it to it's root
		firstPerson = true;															//and turn the firstperson bool to true
																					//to reset it
	}
}


