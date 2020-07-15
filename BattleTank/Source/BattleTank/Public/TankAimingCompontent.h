// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankAimingCompontent.generated.h" //Put new includes above this

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingCompontent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingCompontent();

	void SetBarrleReference(UStaticMeshComponent* BarrelToSet);

	//TODO add SetTurretReference

	void AimAt(FVector InHitLocation, float InLaunchSpeed);

private:
	UStaticMeshComponent* Barrel = nullptr;

	void MoveBarrelTowards(FVector InAimDirection);
};
