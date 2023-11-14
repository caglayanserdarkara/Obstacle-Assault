#include "MovingPlatform.h"

#include "ToolContextInterfaces.h"

AMovingPlatform::AMovingPlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation();

	FString Name = GetName();


	UE_LOG(LogTemp, Display, TEXT("BeginPlay: %s"), *Name);
}


void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
}

void AMovingPlatform::MovePlatform(float DeltaTime)
{
	if (ShouldPlatformReturn())
	{
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		StartLocation = StartLocation + MoveDirection * MoveDistance;
		SetActorLocation(StartLocation);
		PlatformVelocity = -PlatformVelocity;
	}
	else
	{
		FVector CurrentLocation = GetActorLocation();
		// Move Platform forwards
		CurrentLocation = CurrentLocation + PlatformVelocity * DeltaTime;
		SetActorLocation(CurrentLocation);
	}
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	AddActorLocalRotation(RotationVelocity * DeltaTime);
}

bool AMovingPlatform::ShouldPlatformReturn() const //Pure function
{
	return (GetDistanceMoved() > MoveDistance);
}

float AMovingPlatform::GetDistanceMoved() const //Pure function
{
	float Distance = FVector::Dist(StartLocation, GetActorLocation());
	return Distance;
}
