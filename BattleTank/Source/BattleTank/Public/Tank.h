// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TankAimingCompontent.h"
#include "CoreMinimal.h" //Possibly new includes above this too
#include "GameFramework/Pawn.h"
#include "Tank.generated.h" //Put new includes above this

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void AimAt(FVector InHitLocation);

protected:
	UTankAimingCompontent* TankAimingComponent = nullptr;

private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
