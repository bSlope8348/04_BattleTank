// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

//The Turret rotates the barrel.
UCLASS(meta = (BlueprintSpawnableComponent)) //, hidecategories = ("Collision")
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	//-1 max downward speed, and +1 max upward speed
	void Elevate(float RelativeSpeed);

private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxDegreesPerSecond = 5; //Sensible defaults
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MinElevation = 0;
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxElevation = 40;

};
