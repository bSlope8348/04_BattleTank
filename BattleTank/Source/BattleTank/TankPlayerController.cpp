// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogTemp, Warning, TEXT("PlayerConroller Begin Play"));

	if (!GetControlledTank())
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerController not possessing a tank."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController Tank possessed: %s."), *GetControlledTank()->GetName());
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
	if (!GetControlledTank()) { return; }

	//If crosshair hits the landscape
		//Tell controlled tank to aim at this point
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation)) //Has "side-effect", is going to line trace
	{	
		//UE_LOG(LogTemp, Warning, TEXT("Look Location: %s"), *ScreenLocation.ToString());
	}
	//if does not hit world
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Hit Location"));
	}
}

// Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	//Get world location of linetrace through crosshair
	//if hits world use out parameter for hit location
	
	//Find the cross hair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);
	
	//"De-project" the screen position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		UE_LOG(LogTemp, Warning, TEXT("Look Direction: %s"), *LookDirection.ToString());
	}

	//Line-trace along that look direction, and see what we hit (up to max range)
	
	
	//If hit landscape return true
	//else return false
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D OutScreenLocation, FVector& OutLookDirection) const
{
	FVector CameraWorldLocation;//To be discarded
	DeprojectScreenPositionToWorld(
		OutScreenLocation.X, 
		OutScreenLocation.Y, 
		CameraWorldLocation, 
		OutLookDirection);
	return true;
}
