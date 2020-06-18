// Fill out your copyright notice in the Description page of Project Settings.

#include"Engine/World.h"
#include "TankAimingComponent.h"
#include "Tank.h"
#include"Kismet/GameplayStatics.h"
#include "SaveProgress.h"
#include"Kismet/GameplayStatics.h"
#include "MenuSwitchGameInstance.h"

void UMenuSwitchGameInstance::Init() {
	Super::Init();
	if (!UGameplayStatics::DoesSaveGameExist("CheckPoint", 0)) {
		//create instance of USaveProgress
		SaveGameInstance = Cast<USaveProgress>(UGameplayStatics::CreateSaveGameObject(USaveProgress::StaticClass()));
		UE_LOG(LogTemp, Warning, TEXT("CREATED REF"));
	}
	else if (UGameplayStatics::DoesSaveGameExist("CheckPoint", 0)) {
		FAsyncLoadGameFromSlotDelegate LoadedDelegate;
		//Load GameInstance of USaveProgress
		LoadedDelegate.BindUObject(this, &UMenuSwitchGameInstance::LoadGameDelegateFunction);
		UGameplayStatics::AsyncLoadGameFromSlot("CheckPoint", 0, LoadedDelegate);
	}
}

void UMenuSwitchGameInstance::SavedPlayerStatus() {
	FAsyncSaveGameToSlotDelegate SavedDelegate;
	SavedDelegate.BindUObject(this, &UMenuSwitchGameInstance::SaveGameDelegateFunction);
	auto player = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto AmmingRef = player->FindComponentByClass<UTankAimingComponent>();
	//Saving Position of Player
	SaveGameInstance->PlayerPosition = player->GetActorLocation();
	SaveGameInstance->PlayerLife = Cast<ATank>(player)->ReturnCurrentHealth();
	SaveGameInstance->MachinegunAmmo = AmmingRef->GetCurrentGunBullet();
	SaveGameInstance->TankAmmo = AmmingRef->GetTankBullet();
	SaveGameInstance->MaxMachinegunAmmo = AmmingRef->GetMaxGunBullet();
	//Save the USaveProgress Instance
	UGameplayStatics::AsyncSaveGameToSlot(SaveGameInstance, TEXT("CheckPoint"), 0, SavedDelegate);
}

void UMenuSwitchGameInstance::LoadPlayerStatus() {
	auto PlayerRef = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto AimComponent = PlayerRef->FindComponentByClass<UTankAimingComponent>();
	FHitResult Hit;
	PlayerRef->SetActorLocation(SaveGameInstance->PlayerPosition, false, &Hit, ETeleportType::TeleportPhysics);
	AimComponent->RetrievedSavedAmmo(SaveGameInstance->TankAmmo, SaveGameInstance->MachinegunAmmo, SaveGameInstance->MaxMachinegunAmmo);
	Cast<ATank>(PlayerRef)->ReSpawn(SaveGameInstance->PlayerLife);
	//
}

void UMenuSwitchGameInstance::SaveGameDelegateFunction(const FString& SlotName, const int32 UserIndex, bool bSuccess) {
	if (bSuccess) {
		UE_LOG(LogTemp, Warning, TEXT("SuccessSaved"));
	}
}

void UMenuSwitchGameInstance::LoadGameDelegateFunction(const FString& SlotName, const int32 UserIndex, USaveGame* LoadedGameData) {
	UE_LOG(LogTemp, Warning, TEXT("Loaded REF"));
	SaveGameInstance = Cast<USaveProgress>(LoadedGameData);
}
