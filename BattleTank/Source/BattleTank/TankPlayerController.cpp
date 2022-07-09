// Copyright EmbraceIT Ltd.


#include "TankPlayerController.h"
#include "TankAimingCompontent.h"
#include "Public/Tank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingCompontent>();
	if (!ensure(AimingComponent))
	{
		FoundAimingComponent(AimingComponent);
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();

}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!ensure(GetControlledTank())) { return; }

	//If crosshair hits the landscape
		//Tell controlled tank to aim at this point
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation)) //Has "side-effect", is going to line trace
	{	
		GetControlledTank()->AimAt(HitLocation);
	}
	//if does not hit world
	else
	{
		{ return; }
	}
}

// Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	//Find the cross hair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	
	//"De-project" the screen position of the crosshair to a world direction
	FVector LookDirection;
	FVector CameraLocation;
	if (GetLookDirection(ScreenLocation, CameraLocation, LookDirection))
	{
		//Line-trace along that look direction, and see what we hit (up to max range)
		GetLookVectorHitLocation(CameraLocation, LookDirection, OutHitLocation);
	}
		
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D InScreenLocation, FVector& OutCameraWorldLocation, FVector& OutLookDirection) const
{
	DeprojectScreenPositionToWorld(
		InScreenLocation.X, 
		InScreenLocation.Y, 
		OutCameraWorldLocation, 
		OutLookDirection);
	return true;
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector& InCameraWorldLocation, FVector& InLookDirection, FVector& OutHitLocation) const
{
	FHitResult HitResult;
	if (GetWorld()->LineTraceSingleByChannel(
			HitResult,
			InCameraWorldLocation,
			InCameraWorldLocation + (InLookDirection * LineTraceRange),
			ECollisionChannel::ECC_Visibility
			))
	{
		OutHitLocation = HitResult.Location;
		return true;
	}
	OutHitLocation = FVector(0);
	return false; //Line trace didn't succeed
}
