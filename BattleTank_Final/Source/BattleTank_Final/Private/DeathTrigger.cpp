// Fill out your copyright notice in the Description page of Project Settings.

#include "DeathTrigger.h"
#include "MenuSwitchGameInstance.h"
#include "BattleTank_FinalGameModeBase.h"
#include "Components/BoxComponent.h"

// Sets default values
ADeathTrigger::ADeathTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	DeathTrigger = CreateDefaultSubobject<UBoxComponent>(FName("DeathTriger"));
	RootComponent = DeathTrigger;
}

// Called when the game starts or when spawned
void ADeathTrigger::BeginPlay()
{
	Super::BeginPlay();
	DeathTrigger->OnComponentBeginOverlap.AddDynamic(this, &ADeathTrigger::CheckPoint);
	DeathTrigger->OnComponentEndOverlap.AddDynamic(this, &ADeathTrigger::OnCheckPointEnd);
}

void ADeathTrigger::CheckPoint(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (DOOnce) {
		if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr)) {
			auto GameInstanceRef= Cast<UMenuSwitchGameInstance>(GetWorld()->GetGameInstance());
			if (!GameInstanceRef) { return; }
			auto player = GetWorld()->GetFirstPlayerController()->GetPawn();
			if (OtherActor == player)
			{
				GameInstanceRef->SavedPlayerStatus();
				DOOnce = false;
				UE_LOG(LogTemp, Warning, TEXT("CheckPointIn"));
			}
		}
	}
}

void ADeathTrigger::OnCheckPointEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex){
	DOOnce = true;
	UE_LOG(LogTemp, Warning, TEXT("CheckPointOut"));
}

