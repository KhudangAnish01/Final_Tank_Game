// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class AProjectile;
class UTankTurret;
class UTankBarrel;
class UTankAimingComponent;
class UTankMovementComponent;

UCLASS()
class BATTLETANK_FINAL_API ATank : public APawn
{
	GENERATED_BODY()

public:
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void Fire();

	UPROPERTY(EditDefaultsOnly, Category =" Setup")
		TSubclassOf<AProjectile> ProjectileBlueprint;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* TankAimingComponent = nullptr;

private:
	// Sets default values for this pawn's properties
	ATank();

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ReloadTimeInSecond = 3;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 8000;//starting value with 1000m/s cause in ue4 all loaction is in cm

	//Local Barrel Reference
	UTankBarrel* Barrel = nullptr;//TODO Remove

	double LastFireTime = 0;

};
