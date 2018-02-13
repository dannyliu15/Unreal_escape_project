// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Classes/Components/PrimitiveComponent.h"
#include "Engine/CollisionProfile.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "Engine/World.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOpenRequest);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();
	void OpenDoor();
	void CloseDoor();

	UPROPERTY(BlueprintAssignable)
	FOnOpenRequest OnOpenRequest;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	UPROPERTY(EditAnywhere)
	float OpenAngle = 85.0f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr;
	
	UPROPERTY(EditAnywhere)
	float DoorCloseDelay = 0.6f;

	float LastDoorOpenTime;
		
	// The owning door
	AActor* Owner = nullptr;

	// Return total mass into kilogram
	float GetTotalMassOfActorsOnPlate();

};
