// Copyright Rone 2019

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
//#include "GameFramework/PlayerController.h"

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
}

void UOpenDoor::OpenDoor()
{
	Owner->SetActorRotation(FRotator(0.f, OpenAngle, 0.f));
}

void UOpenDoor::CloseDoor()
{
	Owner->SetActorRotation(FRotator(0.f, 0.f, 0.f));
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Poll trigger volume
	if (GetTotalMassOfActorsOnPlate() > 30.f) {
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

	//Check if time to close door
	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay) {
		CloseDoor();
	}
}

float UOpenDoor::GetTotalMassOfActorsOnPlate() {
	float TotalMass = 0.f;

	//Find all overlapping actors.
	TArray<AActor*> OverlappingActors;
	PressurePLate->GetOverlappingActors(OUT OverlappingActors);
	//Iterate through and add masses.
	for (const auto& Actor : OverlappingActors) {
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("%s object on plate."), *Actor->GetName())
	}

	return TotalMass;
}

