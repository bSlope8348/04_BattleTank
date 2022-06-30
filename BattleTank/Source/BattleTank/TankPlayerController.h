// Copyright EmbraceIT Ltd.

#pragma once

#include "Engine/World.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" //Must be the last include

//Forward Declatation
class ATank;
class UTankAimingCompontent;

/**
 * Responsible for helping the player aim
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	UFUNCTION(Blueprintcallable, Category = "Setup")
	ATank* GetControlledTank() const;

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingCompontent* AimCompRef);

private:
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Start the tank moving the barrel so that a shot would hit where the crosshair intersects the world
	void AimTowardsCrosshair();
	
	//Return an OUT parameter, true if hit landscape
	bool GetSightRayHitLocation(FVector& OutHitLocation) const;

	bool GetLookDirection(FVector2D InScreenLocation, FVector& OutCameraWorldLocation, FVector& OutLookDirection) const;

	bool GetLookVectorHitLocation(FVector& InCameraWorldLocation, FVector& InLookDirection, FVector& OutHitLocation) const;

	// Crosshair location
	UPROPERTY(EditDefaultsOnly)
	float CrossHairXLocation = 0.5;
	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation = 0.33333;
	
	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000;

};
