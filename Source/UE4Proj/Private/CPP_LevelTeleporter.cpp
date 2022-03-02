// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/Actor.h"
#include "CustomFPCharacter.h"
#include "CPP_CharacterController.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "CPP_LevelTeleporter.h"

// Sets default values
ACPP_LevelTeleporter::ACPP_LevelTeleporter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create the TriggerBox
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	//Bind the overlap events to functions
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ACPP_LevelTeleporter::OnBoxBeginOverlap);
}

// Called when the game starts or when spawned
void ACPP_LevelTeleporter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_LevelTeleporter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPP_LevelTeleporter::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);		//Get the player character and pass in the instance of the world
	if (playerCharacter->GetUniqueID() == OtherActor->GetUniqueID())						//Checks whether the player has overlapped with the TriggerBox
	{
		UGameplayStatics::OpenLevel(this, LevelName);										//Open the level in coordination to what is named in the editor
																							//Will open "CPP_Door" if "CPP_Door" is in the editor field
	}
}
