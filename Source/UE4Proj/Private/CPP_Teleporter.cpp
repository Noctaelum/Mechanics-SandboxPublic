// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Teleporter.h"

ACPP_Teleporter::ACPP_Teleporter()
{
	OnActorBeginOverlap.AddDynamic(this, &ACPP_Teleporter::EnterTeleporter);	//when there is an actor that begins to overlap with the teleport box
																				//call the function EnterTeleporter
	OnActorEndOverlap.AddDynamic(this, &ACPP_Teleporter::ExitTeleporter);		//when an actor leaves the overlap with the teleport box
																				//calls on the ExitTeleporter Function
	teleporting = false;
}

void ACPP_Teleporter::BeginPlay()
{
	Super::BeginPlay();
}

void ACPP_Teleporter::EnterTeleporter(class AActor* overlappedActor, class AActor* otherActor)
{
	if (otherActor && otherActor != this)		//check whether an actor actually has overlapped
	{
		if (otherTeleporter)					//checking for null errors
		{
			ACPP_CharacterController* otherCharacter = Cast<ACPP_CharacterController>(otherActor);
			ACustomFPCharacter* character = Cast<ACustomFPCharacter>(otherActor);	//taking the other actor that has overlapped the trigger box
																					//if that actor is of class "ACustomFPCharacter", it takes it and assigns it
																					//to the pointer called "Actor"
			if (otherCharacter && !otherTeleporter->teleporting)							//gets the teleporting bool from the other teleporter and makes sure that it's false
																					//because if it's false it means that the player hasn't been teleported
			{
				teleporting = true;
				otherCharacter->SetActorRotation(otherTeleporter->GetActorRotation());
				otherCharacter->GetController()->SetControlRotation(otherCharacter->GetActorRotation());
				otherCharacter->SetActorLocation(otherTeleporter->GetActorLocation());
			}
		}
	}
}

void ACPP_Teleporter::ExitTeleporter(class AActor* overlappedActor, class AActor* otherActor)
{
	if (otherActor && otherActor != this)				//make sure that there is an actor that has been overlapped with
														//also making sure that the actor is not the SAME actor
	{
		if (otherTeleporter && !teleporting)			//check that there is another teleporter and that the player is not teleporting in it
		{
			otherTeleporter->teleporting = false;		//makes sure that the player is not stuck in a teleporting loop
														//player is not entering and exiting the same teleporter
		}
	}
}