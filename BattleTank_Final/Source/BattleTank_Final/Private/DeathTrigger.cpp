// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Tank.h"
#include"Kismet/GameplayStatics.h"
#include "SaveProgress.h"
#include "BattleTank_FinalGameModeBase.h"
#include "Components/BoxComponent.h"
#include "DeathTrigger.h"

// Sets default values
ADeathTrigger::ADeathTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DeathTrigger = CreateDefaultSubobject<UBoxComponent>(FName("DeathTriger"));
	RootComponent = DeathTrigger;
}

// Called when the game starts or when spawned
void ADeathTrigger::BeginPlay()
{
	Super::BeginPlay();
	DeathTrigger->OnComponentBeginOverlap.AddDynamic(this, &ADeathTrigger::CheckPoint);
}

// Called every frame
void ADeathTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADeathTrigger::CheckPoint(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr)) {

		auto player = GetWorld()->GetFirstPlayerController()->GetPawn();
		if (OtherActor == player)
		{
			auto AmmingRef = player->FindComponentByClass<UTankAimingComponent>();
			//create instance of our USaveProgress
			USaveProgress* SaveProgressInstance =Cast<USaveProgress>(UGameplayStatics::CreateSaveGameObject(USaveProgress::StaticClass()));//casting int USaveProgress cause CreateSaveGameObject create USaveGame object;
			//Saving Position of Player
			SaveProgressInstance->PlayerPosition = player->GetActorLocation();
			SaveProgressInstance->PlayerLife = Cast<ATank>(player)->ReturnCurrentHealth();
			SaveProgressInstance->MachinegunAmmo = AmmingRef->GetCurrentGunBullet();
			SaveProgressInstance->TankAmmo = AmmingRef->GetTankBullet();
			SaveProgressInstance->MaxMachinegunAmmo = AmmingRef->GetMaxGunBullet();
			//Save the USaveProgress Instance
			UGameplayStatics::SaveGameToSlot(SaveProgressInstance, TEXT("CheckPoint"), 0);
		}
	}
}

