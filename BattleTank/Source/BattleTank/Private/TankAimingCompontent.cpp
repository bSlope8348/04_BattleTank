// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"
#include "TankAimingCompontent.h"

// Sets default values for this component's properties
UTankAimingCompontent::UTankAimingCompontent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true; //TODO Should this really tick?

	// ...
}

void UTankAimingCompontent::SetBarrleReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingCompontent::AimAt(FVector InHitLocation, float InLaunchSpeed)
{
	if (!Barrel) {	return;	}

	FVector OutLaunchVelocity(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		InHitLocation,
		InLaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace //Parameter must be present to prevent bug
	);
	if (bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: Aim solution found."), Time);
	}
	//If no solution do nothing
	else 
	{
		auto Time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f: No Aim Solution!!!"), Time);
	}
}

void UTankAimingCompontent::MoveBarrelTowards(FVector InAimDirection)
{
	//Work-out difference between current barrel rotation, and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = InAimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	//UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *AimAsRotator.ToString());
	
	Barrel->Elevate(5); //TODO remove magic number

}
