// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Ladder.h"
#include "GameFramework/Actor.h"
#include "CustomFPCharacter.h"
#include "CustomPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/EngineTypes.h"
//Other includes
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"

// Sets default values
ACPP_Ladder::ACPP_Ladder()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//create the mesh component for the ladder
	LadderMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LadderMesh"));
	LadderMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	//trigger box 
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ACPP_Ladder::OnBoxBeginOverlap);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ACPP_Ladder::OnBoxEndOverlap);
}

// Called when the game starts or when spawned
void ACPP_Ladder::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_Ladder::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPP_Ladder::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACustomFPCharacter* playerChar;
	ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);	//checking whether it's the character controller
	if (playerCharacter->GetUniqueID() == OtherActor->GetUniqueID())					//that has collided with the box collider
	{
		playerChar->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
	}
}

void ACPP_Ladder::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (playerCharacter->GetUniqueID() == OtherActor->GetUniqueID())
	{
	
	}
}


