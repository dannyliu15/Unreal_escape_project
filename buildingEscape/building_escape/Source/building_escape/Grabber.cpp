// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"


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
	
	FindPhysicsHandleComponent();
	FindInputHandleComponent();

}

void UGrabber::FindInputHandleComponent()
{
	InputHandle = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputHandle)
	{
		UE_LOG(LogTemp, Warning, TEXT(" Find InputHandle, calling object: %s !"), *GetOwner()->GetName());
		/// Bind the input axis
		InputHandle->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputHandle->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{

		UE_LOG(LogTemp, Error, TEXT(" Failed to find InputHandle, calling object: %s !"), *GetOwner()->GetName());

	}
}

void UGrabber::FindPhysicsHandleComponent()
{
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
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// if the physics handle is attached
	if (PhysicsHandle->GrabbedComponent)
	{
		// move the object that we're holding
		FVector PlayerViewPointLocation;
		FRotator PlayerViewPointRotation;
		GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
			OUT PlayerViewPointLocation,
			OUT PlayerViewPointRotation);
		FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * reach;

		PhysicsHandle->SetTargetLocation(LineTraceEnd);

	}
	
}

void UGrabber::MyDrawDebugLine(FVector &PlayerViewPointLocation, FVector &LineTraceEnd)
{
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
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT(" Grab function called"));

	// LineTrace: Try and reach any actors with physics body collision channel set
	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();
	AActor *ActorHit = HitResult.GetActor();

	// If we hit somethng then attach a physics handle
	if (ActorHit)
	{
		// attach physics handle
		/// Get player view point this tick
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			ComponentToGrab,
			NAME_None,
			ComponentToGrab->GetOwner()->GetActorLocation(),
			ComponentToGrab->GetOwner()->GetActorRotation()
		);
	}
	
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT(" Release function called"));
	PhysicsHandle->ReleaseComponent();
	// TODO release physics handle

}

FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	/// Get player view point 
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation);
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * reach;


	// MyDrawDebugLine(PlayerViewPointLocation, LineTraceEnd);

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
		return Hit;
	}

	return Hit;
}

