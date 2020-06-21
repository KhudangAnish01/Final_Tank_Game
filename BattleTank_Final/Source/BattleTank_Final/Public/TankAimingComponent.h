// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankTurret;
class UTankBarrel;
class AProjectile;

UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked,
	OutOfAmmo
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_FINAL_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Setup")
		void initialse(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = "Firing")
		void Fire();

	UFUNCTION(BlueprintCallable, Category = "Firing")
		void FireBullet();

	EFiringState GetFiringState() const;

	//For Tank
	UFUNCTION(BlueprintCallable, Category = "Firing")
		int GetTankBullet() const;

	//For MachineGun
	UFUNCTION(BlueprintCallable, Category = "Firing")
		int GetMaxGunBullet() const;

	UFUNCTION(BlueprintCallable, Category = "Firing")
		int GetCurrentGunBullet() const;

	//For Damage
	void AcceptDamagePoint(float HitPoint);

	float DamagePoint;

	void GetGrabbedTankAmmo(int GrabTankAmmo);

	void GetGrabbedGunAmmo(int GrabGunAmmo);

	void RetrievedSavedAmmo(int TankAmmo, int GunAmmo,int MaxGunAmmo);

	//for MachineGun
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Firing")
		int CurrentGunBullet = 30;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Firing")
		int MaxGunBullett = 120;

	//for Tank
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Firing")
		int TankRoundsLeft = 30;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = "fire")
		EFiringState FiringState;

	UPROPERTY(EditDefaultsOnly, Category = " Setup")
		TSubclassOf<AProjectile> ProjectileBlueprint;//Tank Ammo spawn

	UPROPERTY(EditDefaultsOnly, Category = " Setup")//Gun Ammo spawn
		TSubclassOf<AProjectile> ProjectileBlueprint1;

	UFUNCTION(BlueprintCallable, Category = "Reload")
	void Reloading();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void MoveBarrelTowards(FVector AimDirection);

private:
	// Sets default values for this component's properties
	UTankAimingComponent();

	bool IsBarrelMoving();

	UPROPERTY(EditDefaultsOnly, Category = "Firing")//starting value with 1000m/s cause in ue4 all loaction is in cm
		float LaunchSpeed = 3000;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ReloadTimeInSecond = 3;//holds fire for 3 second

	//for MachineGun
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		int MagazineSize =30 ;

	UTankBarrel* Barrel = nullptr;

	UTankTurret* Turret = nullptr;

	double LastFireTime = 0;

	FVector AimDirection;//Drection that define where is normal unit arrow is forwarding;

	float ReloadTimeGun = 2;

	void Delay();

	bool IsReloading=true;

};
