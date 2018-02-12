// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Classes/Components/PrimitiveComponent.h"
#include "Engine/EngineTypes.h"
#include "Runtime/Engine/Classes/Components/InputComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Grabber.generated.h"



struct LineTraceInfo
{
	FVector end;
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;





public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Get the hit result
	FHitResult GetPhysicsHitResultInReach();
	
	LineTraceInfo GetReachLine();

	// Draw the debug line from player position to LineTraceEnd
	void MyDrawDebugLine(FVector &PlayerViewPointLocation, FVector &LineTraceEnd);
	
	// Find (assumed) attached physics handle
	void FindPhysicsHandleComponent();
	
	// Setup (assumed) attached input component
	void FindInputHandleComponent();

private:
	// How far ahead of the player can we reach in cm
	float reach = 100.0f;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	
	UInputComponent* InputHandle = nullptr;

	// Ray-cast and grab what's in reach
	void Grab();

	// Ray-cast and release what's in reach
	void Release();

};
