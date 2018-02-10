// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Engine/EngineTypes.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT(" Grabber reporting for duty !"));
	
	/// Look for attached Physics Handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{
		// 
	}
	else
	{

		UE_LOG(LogTemp, Error, TEXT(" Failed to find PhysicsHandle, calling object: %s !"), *GetOwner()->GetName());

	}
	InputHandle = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputHandle)
	{
		UE_LOG(LogTemp, Warning, TEXT(" Find InputHandle, calling object: %s !"), *GetOwner()->GetName());
		/// Bind the input axis
		InputHandle->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
	}
	else
	{

		UE_LOG(LogTemp, Error, TEXT(" Failed to find InputHandle, calling object: %s !"), *GetOwner()->GetName());

	}

}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	/// Get player view point this tick
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation, 
		OUT PlayerViewPointRotation);
	//UE_LOG(LogTemp, Warning, TEXT(" Player location: %s, Player rotation: %s "), *PlayerLocation.ToString(), *PlayerRotation.ToString()  );

	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * reach;


	DrawDebugLine(
		GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor(0, 0, 255),
		false,
		0.f,
		0,
		10.0f
	);

	/// Setup query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());


	/// Line-trace (Ray-cast) out to reach distance
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	/// See what we hit
	AActor* ObjectHit = Hit.GetActor();
	if (ObjectHit)
	{
		// MUST check if ObjectHit is not NULL !!!
		UE_LOG(LogTemp, Warning, TEXT(" Line-trace hit on %s "), *ObjectHit->GetName());
	}

}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT(" Grab function called"));

}

