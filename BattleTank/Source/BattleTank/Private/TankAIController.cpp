// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogTemp, Warning, TEXT("AIConroller Begin Play"));

	if (!GetAIControlledTank())
	{
		UE_LOG(LogTemp, Error, TEXT("AIController not possessing a tank."));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController Tank: %s."), *GetAIControlledTank()->GetName());
	}
}

ATank* ATankAIController::GetAIControlledTank() const
{

	return Cast<ATank>(GetPawn());
}
