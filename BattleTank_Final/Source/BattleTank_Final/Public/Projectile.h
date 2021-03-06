// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include"GameFramework/ProjectileMovementComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class URadialForceComponent;

UCLASS()
class BATTLETANK_FINAL_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();
	void LaunchProjectile(float speed);

	void GetProjectileDamage(float DamagePoint);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnyWhere, Category = "Setup")//no advantage use of uproperty
		float ProjectileDamage = 0.0;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float DelayDestory=10.f;

	void OnTimerExpire();

	UProjectileMovementComponent* ProjectileMovement = nullptr;

	UPROPERTY(VisibleAnyWhere,Category="Component")
	UStaticMeshComponent* TankAmmo = nullptr;

	UPROPERTY(VisibleAnyWhere, Category = "Component")
	UParticleSystemComponent* LaunchBlast = nullptr;

	UPROPERTY(VisibleAnyWhere, Category = "Component")
	UParticleSystemComponent* ImpactBlast = nullptr;

	UPROPERTY(VisibleAnyWhere, Category = "Component")
	URadialForceComponent* ExplosionForce = nullptr;
};
