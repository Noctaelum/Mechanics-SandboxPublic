// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_Door.h"
#include "GameFramework/Actor.h"
#include "CustomFPCharacter.h"
#include "CPP_CharacterController.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"


// Sets default values
ACPP_Door::ACPP_Door()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create the DoorMesh component
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	//Create the TriggerBox
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	//Create the TriggerBox for the opposite opening of the door
	OtherTriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("OtherTriggerbox"));
	OtherTriggerBox->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	//Bind the overlap events to functions
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ACPP_Door::OnBoxBeginOverlap);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ACPP_Door::OnBoxEndOverlap);

	//Bind the overlap events to functions
	OtherTriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ACPP_Door::OnBoxBeginOverlapOpposite);
	OtherTriggerBox->OnComponentEndOverlap.AddDynamic(this, &ACPP_Door::OnBoxEndOverlapOpposite);
}

// Called when the game starts or when spawned
void ACPP_Door::BeginPlay()
{
	Super::BeginPlay();

	//Rotator setup
	ClosedRotation = DoorMesh->GetComponentRotation();
	DesiredRotation = DoorMesh->GetComponentRotation();
	OpenRotation = DoorMesh->GetComponentRotation() + FRotator(0.0f, 90.0f, 0.0f);
	NewClosedRotation = DoorMesh->GetComponentRotation() + FRotator(0.0f, 0.0f, 0.0f);
	OtherOpenRotation = DoorMesh->GetComponentRotation() + FRotator(0.0f, -90.0f, 0.0f);
}

// Called every frame
void ACPP_Door::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FRotator CurrentRotation = DoorMesh->GetComponentRotation();						//Get the current rotation of the door
	if (!CurrentRotation.Equals(DesiredRotation, 5.0f))										//if the current rotation is not equal to the DesiredRotation then
	{
		const FRotator NewRotation = FMath::Lerp(CurrentRotation, DesiredRotation, 0.10f);	//Then lerp between CurrentRotation & DesiredRotation
		DoorMesh->SetWorldRotation(NewRotation);											//Dependent on what the lerp returns, set the Rotation to 
																							//The new rotation
	}
	else if (!CurrentRotation.Equals(DesiredRotation, -5.0f))
	{
		const FRotator OppositeNewRotation = FMath::Lerp(CurrentRotation, DesiredRotation, 0.10f);
		DoorMesh->SetWorldRotation(OppositeNewRotation);
	}
}

#pragma region Open Door One way
void ACPP_Door::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//ACustomFPCharacter* character = Cast<ACustomFPCharacter>(OtherActor);

	ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);		//Get the player character and pass in the instance of the world
	if (playerCharacter->GetUniqueID() == OtherActor->GetUniqueID())						//Checks whether the player has overlapped with the TriggerBox
	{
		DesiredRotation = OpenRotation;														//If so then change the DesiredRotation to the OpenRotation
	}
}

void ACPP_Door::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);		//Get the player character and pass in the instance of the world
	if (playerCharacter->GetUniqueID() == OtherActor->GetUniqueID())						//Checks whether the player has overlapped with the TriggerBox
	{
		DesiredRotation = ClosedRotation;														//If so then change the DesiredRotation to the OpenRotation
	}
}
#pragma endregion

#pragma region Open Opposite way 

void ACPP_Door::OnBoxBeginOverlapOpposite(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);		//Get the player character and pass in the instance of the world
	if (playerCharacter->GetUniqueID() == OtherActor->GetUniqueID())						//Checks whether the player has overlapped with the TriggerBox
	{
		DesiredRotation = OtherOpenRotation;												//If so then change the DesiredRotation to the OpenRotation
	}
}

void ACPP_Door::OnBoxEndOverlapOpposite(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	ACharacter* playerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);		//Get the player character and pass in the instance of the world
	if (playerCharacter->GetUniqueID() == OtherActor->GetUniqueID())						//Checks whether the player has overlapped with the TriggerBox
	{
		DesiredRotation = ClosedRotation;													//If so then change the DesiredRotation to the OpenRotation
	}
}

#pragma endregion

