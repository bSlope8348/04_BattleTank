// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankAimingCompontent.generated.h" //Put new includes above this

//Forward Declaration
class UTankBarrel; 

//Holds barrel's properties and Elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingCompontent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingCompontent();

	void SetBarrleReference(UTankBarrel* BarrelToSet);

	//TODO add SetTurretReference

	void AimAt(FVector InHitLocation, float InLaunchSpeed);

private:
	UTankBarrel* Barrel = nullptr;

	void MoveBarrelTowards(FVector InAimDirection);
};
