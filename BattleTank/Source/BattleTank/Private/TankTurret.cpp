// Fill out your copyright notice in the Description page of Project Settings.


#include "Math/UnrealMathUtility.h"
#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	//Move the turret the right amount this frame, Given a max rotation speed, and the frame time
	auto RotationChange = FMath::Clamp<float>(RelativeSpeed, -1, 1) * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewRotation = GetRelativeRotation().Yaw + RotationChange;
	//auto NewRotation = FMath::Clamp(RawNewRotation, MinRotation, MaxRotation);

	SetRelativeRotation(FRotator(0, RawNewRotation, 0));

}
