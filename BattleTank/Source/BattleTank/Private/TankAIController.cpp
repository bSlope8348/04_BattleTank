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

	if (!GetPlayerTank())
	{
		UE_LOG(LogTemp, Error, TEXT("AIController %s can't find a PlayerController tank."), *GetAIControlledTank()->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController %s found PlayerController Tank: %s."), *GetAIControlledTank()->GetName(), *GetPlayerTank()->GetName());
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetPlayerTank())
	{
		//TODO move towards the player
		
		//Aim towards the player
		AimTowardsPlayerTank();

		//TODO Fire if ready
	}
}

void ATankAIController::AimTowardsPlayerTank()
{
	if (!GetAIControlledTank()) { return; }

	if (GetPlayerTank())
	{
		GetAIControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No Player Location"));
	}
}

ATank* ATankAIController::GetAIControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
		//UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!PlayerPawn) { return nullptr; }

	return Cast<ATank>(PlayerPawn);
}