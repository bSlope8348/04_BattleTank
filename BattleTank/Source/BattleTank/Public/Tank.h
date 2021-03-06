// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h" //Possibly top header?
#include "GameFramework/Pawn.h"
#include "Tank.generated.h" //Put new includes above this

//Forward Declarations
class UTankBarrel;
class UTankTurret;
class UTankAimingCompontent;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void AimAt(FVector InHitLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel* BarrelToSet);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret* TurretToSet);

	//Fire projectile command
	UFUNCTION(BlueprintCallable, Category = Setup)
	void Fire();
	
protected:
	UTankAimingCompontent* TankAimingComponent = nullptr;

private:
	// Sets default values for this pawn's properties
	ATank();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 3;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 9000; // m/s

	double LastFireTime = 0;

	//Local barrel reference for spawning projectile
	UTankBarrel* Barrel = nullptr;
	
};
