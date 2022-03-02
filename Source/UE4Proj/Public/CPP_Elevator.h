// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CustomFPCharacter.h"
#include "CPP_Elevator.generated.h"

//forward decleration
class UBoxComponent;

UCLASS()
class UE4PROJ_API ACPP_Elevator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_Elevator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere, meta=(MakeEditWidget))
	FVector EndPos;

	UPROPERTY(VisibleAnywhere);
	UStaticMeshComponent* ElevatorMesh;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* TriggerBox;

private:
	FVector StartPos;

	FVector DesiredPos;

};
