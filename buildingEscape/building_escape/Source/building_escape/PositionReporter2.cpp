// Copyright Danny Liu 2018

#include "PositionReporter2.h"
#include "GameFramework/Actor.h"


// Sets default values for this component's properties
UPositionReporter2::UPositionReporter2()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}


// Called when the game starts
void UPositionReporter2::BeginPlay()
{
	Super::BeginPlay();
	FString ObjectName = GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("Position reporter 2 reporting test on name: %s "), *ObjectName);
	// ...
	
}


// Called every frame
void UPositionReporter2::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

