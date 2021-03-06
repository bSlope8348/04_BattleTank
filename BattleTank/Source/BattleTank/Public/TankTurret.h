// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

//The turrent sets the point of firing.
UCLASS(meta = (BlueprintSpawnableComponent)) //, hidecategories = ("Collision")
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	//-1 max left rotation speed, and +1 max right rotation speed
	void Rotate(float RelativeSpeed);

private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxDegreesPerSecond = 20; //Sensible defaults
/*	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MinRotation = -90;
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxRotation = 90;
*/

};
