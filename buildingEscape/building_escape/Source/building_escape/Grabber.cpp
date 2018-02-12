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
	if ( ! PhysicsHandle )
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
		PhysicsHandle->SetTargetLocation(GetReachLine().end);
	}
	
}

void UGrabber::Grab()
{
	// LineTrace: Try and reach any actors with physics body collision channel set
	FHitResult HitResult = GetPhysicsHitResultInReach();
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent(); // gets the mesh in our case
	AActor *ActorHit = HitResult.GetActor();

	// If we hit somethng then attach a physics handle
	if (ActorHit)
	{
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			ComponentToGrab,
			NAME_None,// no bones needed
			ComponentToGrab->GetOwner()->GetActorLocation(),
			ComponentToGrab->GetOwner()->GetActorRotation()
		);
	}
	
}

void UGrabber::Release()
{
	PhysicsHandle->ReleaseComponent();
}

FHitResult UGrabber::GetPhysicsHitResultInReach()
{
	//MyDrawDebugLine(
	//	GetReachLine().PlayerViewPointLocation, 
	//	GetReachLine().end);
	/// Setup query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	/// Line-trace (Ray-cast) out to reach distance
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByObjectType(
		OUT HitResult,
		GetReachLine().PlayerViewPointLocation,
		GetReachLine().end,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	///// See what we hit
	//AActor* ObjectHit = HitResult.GetActor();
	//if (ObjectHit)
	//{
	//	// MUST check if ObjectHit is not NULL !!!
	//	UE_LOG(LogTemp, Warning, TEXT(" Line-trace hit on %s "), *ObjectHit->GetName());
	//	return HitResult;
	//}

	return HitResult;
}

LineTraceInfo UGrabber::GetReachLine()
{
	LineTraceInfo GrabLine;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT GrabLine.PlayerViewPointLocation,
		OUT GrabLine.PlayerViewPointRotation);
	GrabLine.end = GrabLine.PlayerViewPointLocation + 
			GrabLine.PlayerViewPointRotation.Vector() * reach;
	return GrabLine;
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
