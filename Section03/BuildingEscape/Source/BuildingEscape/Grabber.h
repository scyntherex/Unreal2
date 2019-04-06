// Copyright Rone 2019

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
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

private:
	//How far ahead of Player is the reach.
	float Reach = 100.f;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;

	void Grab();
	void Release();

	//attached physics handle
	void FindPhysicsHandleComponent();

	//setup input component
	void SetupInputComponent();

	//Return hit for first body in reach
	const FHitResult GetFirstPhysicsBodyInReach();

	//Return line trace start position
	FVector GetLineTraceStart();

	//Return line trace end position
	FVector GetLineTraceEnd();

	//Return line trace rotation
	FRotator GetLineTraceAngle();
};
