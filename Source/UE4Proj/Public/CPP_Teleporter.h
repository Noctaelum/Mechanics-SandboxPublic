// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "GameFramework/Actor.h"
#include "CustomFPCharacter.h"
#include "CPP_CharacterController.h"
#include "GameFramework/SpringArmComponent.h"
#include "CPP_Teleporter.generated.h"

/**
 * 
 */
UCLASS()
class UE4PROJ_API ACPP_Teleporter : public ATriggerBox
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	ACPP_Teleporter();

	UFUNCTION()
		void EnterTeleporter(class AActor* overlappedActor, class AActor* otherActor);

	UFUNCTION()
		void ExitTeleporter(class AActor* overlappedActor, class AActor* otherActor);

	UPROPERTY(EditAnywhere, Category = "Teleporter")	//Editanywhere so that it can be seen anywhere in the details panel
		ACPP_Teleporter* otherTeleporter;				//pointer to the other teleporter in the scene
														//so that the location can be fetched and the player goes to the location.
	UPROPERTY()
		bool teleporting;								//this is used to determine whether a player has teleported
														//so that if the player hits the other teleport box it doesn't teleport the player back to the previous box.

};
