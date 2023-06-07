// Copyright EmbraceIT Ltd.


#include "TankAimingCompontent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingCompontent::UTankAimingCompontent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingCompontent::BeginPlay()
{
	//So that first fire is after initial reload 
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingCompontent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingCompontent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{

	if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringStatus = EFiringStatus::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringStatus = EFiringStatus::Aiming;
	}
	else
	{
		FiringStatus = EFiringStatus::Locked;
	}
}

bool UTankAimingCompontent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	auto BarrelForward = Barrel->GetForwardVector();
	return !BarrelForward.Equals(AimDirection, 0.01);
}

void UTankAimingCompontent::AimAt(FVector InHitLocation)
{
	if (!ensure(Barrel && Turret)) { return; }

	FVector OutLaunchVelocity(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		InHitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace //Parameter must be present to prevent bug
	);
	if (bHaveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
		MoveTurretTowards(AimDirection);
	}
	//If no solution do nothing
}

void UTankAimingCompontent::MoveBarrelTowards(FVector InAimDirection)
{
	if (!ensure(Barrel && Turret)) { return; }

	//Work-out difference between current barrel rotation, and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = InAimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
		
	Barrel->Elevate(DeltaRotator.Pitch);

}

void UTankAimingCompontent::MoveTurretTowards(FVector InAimDirection)
{
	if (!ensure(Barrel && Turret)) { return; }

	//Work-out difference between current Turret rotation, and AimDirection
	auto TurretRotator = Turret->GetForwardVector().Rotation();
	auto AimAsRotator = InAimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - TurretRotator;

	Turret->Rotate(DeltaRotator.Yaw);

}

void UTankAimingCompontent::Fire()
{
	if (FiringStatus != EFiringStatus::Reloading)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Reloaded and Firing"))
		//Spawn a projectile at the socket location of the barrel
		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}
