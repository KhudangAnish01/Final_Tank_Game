// Fill out your copyright notice in the Description page of Project Settings.

#include "SprungWheel.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostPhysics;

	MassWheelConstriant = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("MassWheelConstriant"));
	SetRootComponent(MassWheelConstriant);

	Axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
	Axle->SetupAttachment(MassWheelConstriant);

	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	Wheel->SetupAttachment(Axle);

	AxleWheelConstriant = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("AxleWheelConstriant"));
	AxleWheelConstriant->SetupAttachment(Axle);
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	Wheel->SetNotifyRigidBodyCollision(true);
	Wheel->OnComponentHit.AddDynamic(this, &ASprungWheel::OnHit);
	SetupConstriant();
}

void  ASprungWheel::SetupConstriant()
{
	if (!GetAttachParentActor()) { return; }
	//GetRootComponent() compulsory
	UPrimitiveComponent* BodyTank = Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent());
	if (!BodyTank) { return; }
	MassWheelConstriant->SetConstrainedComponents(BodyTank, NAME_None, Axle, NAME_None);
	AxleWheelConstriant->SetConstrainedComponents(Axle, NAME_None, Wheel, NAME_None);
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetWorld()->TickGroup == TG_PostPhysics) {
		TotalForceForDrive = 0;
	}
}

void ASprungWheel::AddDrivingForce(float ForceForDrive) {
	TotalForceForDrive += ForceForDrive;
}

void ASprungWheel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	ApplyForce();
}

void ASprungWheel::ApplyForce() {
	Wheel->AddForce(Axle->GetForwardVector() * TotalForceForDrive);
}

