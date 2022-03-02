// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CustomFPCharacter.h"
#include "CPP_CharacterController.h"
#include "CPP_Door.generated.h"


//Forward Declaration
class UBoxComponent;

UCLASS()
class UE4PROJ_API ACPP_Door : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACPP_Door();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//Function for when the player starts overlapping with the TriggerBox

	UFUNCTION()
		void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	//Function for when the player stops overlapping with the TriggerBox

	UFUNCTION()
		void OnBoxBeginOverlapOpposite(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnBoxEndOverlapOpposite(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(VisibleAnywhere)
		UBoxComponent* TriggerBox;
	//Box component for the trigger box

	UPROPERTY(VisibleAnywhere)
		UBoxComponent* OtherTriggerBox;

private:
	FRotator DesiredRotation;
	FRotator OpenRotation;
	FRotator ClosedRotation;
	FRotator NewClosedRotation;
	FRotator OtherOpenRotation;
	//Rotators that will allow for the door to open, open to a certain rotation and then close to a certain rotation

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* DoorMesh;
	//Mesh component for the door
};