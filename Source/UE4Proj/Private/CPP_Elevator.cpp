// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Elevator.h"
#include "GameFramework/Actor.h"
#include "CustomFPCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"

// Sets default values
ACPP_Elevator::ACPP_Elevator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create the ElevatorMesh component
	ElevatorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ElevatorMesh"));
	ElevatorMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	//trigger box 
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ACPP_Elevator::OnBoxBeginOverlap);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ACPP_Elevator::OnBoxEndOverlap);

}

// Called when the game starts or when spawned
void ACPP_Elevator::BeginPlay()
{
	Super::BeginPlay();

	//Vector setup
	StartPos = ElevatorMesh->GetComponentLocation();
	DesiredPos = ElevatorMesh->GetComponentLocation();
	EndPos = EndPos + ElevatorMesh->GetComponentLocation();

}

// Called every frame
void ACPP_Elevator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	const FVector CurrentPosition = ElevatorMesh->GetComponentLocation();
	if (!CurrentPosition.Equals(EndPos))												//If the current position is not the end position
	{	
		FVector DirectionToPos = DesiredPos - ElevatorMesh->GetComponentLocation();		//then move the elevator to the desired location and
		DirectionToPos.Normalize();														//make the directiontopos a value of 1

		const FVector NewPos = ElevatorMesh->GetComponentLocation() + DirectionToPos;	//set the new position to the elevator location + DirectionToPos
		ElevatorMesh->SetWorldLocation(NewPos);											//set the elevator to the new position
	}
}

void ACPP_Elevator::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);	//checking whether it's the character controller
	if (playerCharacter->GetUniqueID() == OtherActor->GetUniqueID())					//that has collided with the box collider
	{
		//DesiredPos = EndPos;
		//if the desired pos = the end pos
		//then make desired pos the start pos
		if (DesiredPos == EndPos)														//if the desired position is the end position, then set
		{
			DesiredPos = StartPos;														//the desired position back to the start pos so that it will go back where it came from
		}
		else if (DesiredPos == StartPos)												//and if the desired position is the start position set
		{
			DesiredPos = EndPos;														//desired position back to the end position so it will go to where it needs to go to
		}
	}
}

void ACPP_Elevator::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (playerCharacter->GetUniqueID() == OtherActor->GetUniqueID())
	{
		return;
	}
}

