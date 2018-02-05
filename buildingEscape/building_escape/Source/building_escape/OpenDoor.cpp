// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GameFramework/Controller.h"
#include "GameFramework/WorldSettings.h"

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

	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void UOpenDoor::OpenDoor()
{
	AActor* Owner = GetOwner();
	FRotator ObjectionRotation = Owner->GetActorRotation();
	FRotator DoorRotate(0.0f, -60.0f, 0.0f);
	//UE_LOG(LogTemp, Warning, TEXT("Object before rotation: %s"), *Owner->GetActorRotation().ToString());
	Owner->SetActorRotation(DoorRotate);
	//UE_LOG(LogTemp, Warning, TEXT("Object after rotation: %s"), *Owner->GetActorRotation().ToString());
	// ...
}


void UOpenDoor::CloseDoor()
{
	AActor* Owner = GetOwner();
	FRotator ObjectionRotation = Owner->GetActorRotation();
	FRotator DoorRotate(0.0f, 0.0f, 0.0f);
	//UE_LOG(LogTemp, Warning, TEXT("Object before rotation: %s"), *Owner->GetActorRotation().ToString());
	Owner->SetActorRotation(DoorRotate);
	//UE_LOG(LogTemp, Warning, TEXT("Object after rotation: %s"), *Owner->GetActorRotation().ToString());
	// ...
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the Trigger Volume
	// If the ActorThatOpens is in the volume
	if (PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor();
	}
	else
	{
		CloseDoor();
	}
}

