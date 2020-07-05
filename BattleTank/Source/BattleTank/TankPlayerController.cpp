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

// Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	//Get world location of linetrace through crosshair
	//if hits world use out parameter for hit location
	OutHitLocation = { 0, 1, 2 }; //Out parameter
	
	//If hit landscape return true
	//else return false
	return true;
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	//If crosshair hits the landscape
		//Tell controlled tank to aim at this point
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation)) //Has "side-effect", is going to line trace
	{	
		UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *HitLocation.ToString());
	}
	//if does not hit world
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Hit Location"));
	}
}
