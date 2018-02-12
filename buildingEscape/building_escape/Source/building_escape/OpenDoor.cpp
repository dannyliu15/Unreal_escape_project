// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
}

void UOpenDoor::OpenDoor()
{
	Owner->SetActorRotation(FRotator(0.0f, -1.0 * OpenAngle, 0.0f));
}


void UOpenDoor::CloseDoor()
{
	
	Owner->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.0f;
	TArray<AActor*> OverlappingActors;
	// Find all the overlapping actors
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	// Iterate through then adding their masses
		for (const auto& ptr : OverlappingActors)
		{
			TotalMass += ptr->FindComponentByClass<UPrimitiveComponent>()->GetMass();
			UE_LOG(LogTemp, Warning, TEXT("Ovarlapping Actor: %s"), *ptr->GetName() );
		}
	
	return TotalMass;
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the Trigger Volume
	if ( GetTotalMassOfActorsOnPlate() > 20.0f ) // TODO make into a parameter
	{
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	else
	{
		CloseDoor();
	}


	//if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay)
	//{
	//	CloseDoor();
	//}
   
}

