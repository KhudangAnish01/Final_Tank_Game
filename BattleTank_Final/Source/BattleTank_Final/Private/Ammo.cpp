// Fill out your copyright notice in the Description page of Project Settings.
#include "BattleTank_FinalGameModeBase.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Ammo.h"

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
	UE_LOG(LogTemp, Warning, TEXT("%s"), *FirstName);
}

// Called every frame
void AAmmo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Sphere1->OnComponentBeginOverlap.AddDynamic(this, &AAmmo::GetAmmo);
}

void AAmmo::GetAmmo(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr)) {
		Destroy();
		
	}
}