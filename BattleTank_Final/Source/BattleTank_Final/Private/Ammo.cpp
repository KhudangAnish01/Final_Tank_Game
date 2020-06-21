// Fill out your copyright notice in the Description page of Project Settings.

#include "Ammo.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "BattleTank_FinalGameModeBase.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AAmmo::AAmmo()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sphere1 = CreateDefaultSubobject<USphereComponent>(FName("Collision"));
	RootComponent = Sphere1;

	Create = CreateDefaultSubobject<UStaticMeshComponent>(FName("TankCreate"));
	Create->SetupAttachment(Sphere1);
}

// Called when the game starts or when spawned
void AAmmo::BeginPlay()
{
	Super::BeginPlay();
	ammoname=Create->GetOwner()->GetName();
	ammoname.Split("_", &FirstName, &lastname);
	Sphere1->OnComponentBeginOverlap.AddDynamic(this, &AAmmo::GetAmmo);
}

// Called every frame
void AAmmo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAmmo::GetAmmo(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr)) {

		auto player = GetWorld()->GetFirstPlayerController()->GetPawn();
		if (OtherActor == player)
		{
			Destroy();

			auto AmmoGrabber = OtherActor->FindComponentByClass<UTankAimingComponent>();
			if (FirstName == "TankAmmo") {
				if ((!AmmoGrabber)) { return; }
				AmmoGrabber->GetGrabbedTankAmmo(10);
			}

			if (FirstName == "GunAmmo") {
				if ((!AmmoGrabber)) { return; }
				AmmoGrabber->GetGrabbedGunAmmo(60);
			
			}

			if (FirstName == "MedicalKit") {
				auto HealthGrabber = Cast<ATank>(player);
				if (!HealthGrabber) { return; }
				HealthGrabber->GetMedicalKit(20);
			}
		}
		}
}