// Fill out your copyright notice in the Description page of Project Settings.


#include "Math/UnrealMathUtility.h"
#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	//Move the barrel the right amount this frame, Given a max elevation speed, and the frame time
	auto ElevationChange = FMath::Clamp<float>(RelativeSpeed, -1, 1) * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = GetRelativeRotation().Pitch + ElevationChange;
	auto NewElevation = FMath::Clamp(RawNewElevation, MinElevation, MaxElevation);

	SetRelativeRotation(FRotator(NewElevation, 0, 0));

}
