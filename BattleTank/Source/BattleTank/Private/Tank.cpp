// Copyright EmbraceIT Ltd.


#include "Tank.h"
#include "TankTurret.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankAimingCompontent.h"
#include "TankMovementComponent.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	auto TankName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("DONKEY!!! Constructor C++ %f"), *TankName);
}

void ATank::BeginPlay() 
{
	Super::BeginPlay(); //Needed for BP BeginPlay to Run!
	auto TankName = GetName();
	UE_LOG(LogTemp, Warning, TEXT("DONKEY!!! BeginPlay C++ %f"), *TankName);
}

void ATank::AimAt(FVector InHitLocation)
{
	if (!TankAimingComponent) { return; }
	TankAimingComponent->AimAt(InHitLocation, LaunchSpeed);
}

void ATank::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (Barrel && isReloaded)
	{
	//Spawn a projectile at the socket location of the barrel
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileBlueprint,
		Barrel->GetSocketLocation(FName("Projectile")),
		Barrel->GetSocketRotation(FName("Projectile"))
		);

	Projectile->LaunchProjectile(LaunchSpeed);
	LastFireTime = FPlatformTime::Seconds();
	}
}
