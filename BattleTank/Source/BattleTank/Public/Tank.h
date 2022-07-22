// Copyright EmbraceIT Ltd.

#pragma once

#include "CoreMinimal.h" //Possibly top header?
#include "GameFramework/Pawn.h"
#include "Tank.generated.h" //Put new includes above this

//Forward Declarations
class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	//Fire projectile command
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Fire();
	
protected:


private:
	// Sets default values for this pawn's properties
	ATank();

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3;

	//TODO remove once in Aiming Component 
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 9000; // m/s

	double LastFireTime = 0;

	//Local barrel reference for spawning projectile
	UTankBarrel* Barrel = nullptr;
	
};
