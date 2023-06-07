// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "TankAimingCompontent.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if (!ensure(PlayerTank && ControlledTank)) { 
		UE_LOG(LogTemp, Warning, TEXT("AI Error #1"));
		return; }

	//Move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius); //TODO check radius is in cm

	//Aim towards the player
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingCompontent>();
	if (!ensure(AimingComponent)) { 
		UE_LOG(LogTemp, Warning, TEXT("AI Error #2"));
		return; }
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	AimingComponent->Fire(); //TODO limit fire rate
}
