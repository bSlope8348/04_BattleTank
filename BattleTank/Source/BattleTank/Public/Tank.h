// Copyright EmbraceIT Ltd.

#pragma once

#include "CoreMinimal.h" //Possibly top header?
#include "GameFramework/Pawn.h"
#include "Tank.generated.h" //Put new includes above this

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

private:
	// Sets default values for this pawn's properties
	ATank();

};
