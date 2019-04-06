// Copyright Rone 2019

#include "Grabber.h"


#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandleComponent();

	SetupInputComponent();
}

void UGrabber::FindPhysicsHandleComponent() {
	///Look for attached Physics Handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle) {
		//handle found
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Missing: %s%"), *GetOwner()->GetName());
	}
}

void UGrabber::SetupInputComponent()
{
	///Look for attached Input component
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {
		UE_LOG(LogTemp, Warning, TEXT("Found Component"));
		///Bind Input axis
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Missing: %s%"), *GetOwner()->GetName());
	}
}

void UGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("GRAB Pressed"));

	///Try to reach any physics body collision channel set
	//LineTrace to see if Physics body is detected.
	GetFirstPhysicsBodyInReach();

	//TODO if something is hit, attach physics handle
}

void UGrabber::Release() {
	UE_LOG(LogTemp, Warning, TEXT("RELEASED"));
	//TODO release physics handle
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	//if the physicsa handle is attached
		//move the object that we're holding

	// Get player viewpoint this tick
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation);

	//Log out to test
	/*UE_LOG(LogTemp, Warning, TEXT("Position %s, Rotation %s"),
		*PlayerViewPointLocation.ToString(),
		*PlayerViewPointRotation.ToString());*/

	FVector LineTraceEnd = PlayerViewPointLocation +
		PlayerViewPointRotation.Vector() * Reach;

	//Setup query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	//Ray-cast out to reach distance
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	//see what we hit
	AActor* ObjectPlayerHits = Hit.GetActor();
	if (ObjectPlayerHits) {
		UE_LOG(LogTemp, Warning, TEXT("Line trace hit: %s"),
			*(ObjectPlayerHits->GetName()))
	}
	return FHitResult();
}
