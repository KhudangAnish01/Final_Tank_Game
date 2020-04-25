// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/DamageType.h"
#include"Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Engine/World.h"
#include "Projectile.h"
#include"Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TankAmmo = CreateDefaultSubobject<UStaticMeshComponent>(FName("Tank Ammo"));
	SetRootComponent(TankAmmo);
	TankAmmo->SetNotifyRigidBodyCollision(true);//enable on hit event 
	TankAmmo->SetVisibility(false);
	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	LaunchBlast->AttachToComponent(RootComponent,FAttachmentTransformRules::KeepRelativeTransform);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	ProjectileMovement->bAutoActivate = false;

	ImpactBlast= CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
	ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ImpactBlast->bAutoActivate = false;

	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));
	ExplosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	TankAmmo->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::LaunchProjectile(float speed)
{
	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * speed);
	ProjectileMovement->Activate();
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	LaunchBlast->Deactivate();
	ImpactBlast->Activate();
	ExplosionForce->FireImpulse();//setting impulse force or applying 

	SetRootComponent(ImpactBlast);//we need to set root impact blast cause it make crash while deleting the root
	TankAmmo->DestroyComponent();//destroying tankammo after colliding 

	FTimerHandle Timer;//destroying ammo projrctile from memory
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &AProjectile::OnTimerExpire, DelayDestory, false);
	
	//applying damgae howto for tank
	UGameplayStatics::ApplyRadialDamage(
		this,
		ProjectileDamage,//send damage to tank class
		GetActorLocation(),
		ExplosionForce->Radius,
		UDamageType::StaticClass(),//Returns a UClass object representing this class at runtime
		TArray<AActor*>()//all actors receives the damage
	);
}

void AProjectile::OnTimerExpire()
{
	Destroy();
}
