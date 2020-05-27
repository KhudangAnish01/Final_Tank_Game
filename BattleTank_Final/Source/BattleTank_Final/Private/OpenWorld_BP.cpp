// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "MyGameStateBase.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include"Kismet/GameplayStatics.h"
#include "SaveProgress.h"
#include "MenuSwitchGameInstance.h"
#include "OpenWorld_BP.h"

void AOpenWorld_BP:: BeginPlay(){
	Super::BeginPlay();
	auto GameInstanceRef= Cast<UMenuSwitchGameInstance>(GetGameInstance());
	if (GameInstanceRef->LoadSwitch) {//New Or Continue
		if (UGameplayStatics::DoesSaveGameExist("EnemyStatus", 0)) {
			UGameplayStatics::DeleteGameInSlot("EnemyStatus", 0);
		}
		if (UGameplayStatics::DoesSaveGameExist("CheckPoint", 0)) {
			UGameplayStatics::DeleteGameInSlot("CheckPoint", 0);
		}
		USaveProgress* SaveProgressInstance = Cast<USaveProgress>(UGameplayStatics::CreateSaveGameObject(USaveProgress::StaticClass()));//casting int USaveProgress cause CreateSaveGameObject create USaveGame object;
		UGameplayStatics::SaveGameToSlot(SaveProgressInstance, TEXT("EnemyStatus"), 0);
	}

	if (UGameplayStatics::DoesSaveGameExist("CheckPoint", 0)) {
		SavePlayerStatus();//saving enemy Status
	}

	AMyGameStateBase* const MyGameState = GetWorld() != NULL ? GetWorld()->GetGameState<AMyGameStateBase>() : NULL;
	MyGameState->EnemyDestroyed.AddDynamic(this, &AOpenWorld_BP::BindingFunction);
	LoadingEnemyData();//Loading Saved Data

	//GetAllAcctorOfClass(Getting All AI ref)
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATankAIController::StaticClass(), FoundActors);

	for (auto& AIRef : FoundActors) {
		auto Ref = Cast<ATankAIController>(AIRef);
		bool FindAIRef = SavedData.Contains(Ref);
		if (FindAIRef) {
			Ref->IsEnemyDead = FindAIRef;
			Ref->Update();
			UE_LOG(LogTemp, Warning, TEXT("hello"));
		}
	}
}

void AOpenWorld_BP::LoadingEnemyData() {
	if (UGameplayStatics::DoesSaveGameExist("EnemyStatus", 0)) {
		auto SaveProgressInstance = Cast<USaveProgress>(UGameplayStatics::LoadGameFromSlot("EnemyStatus", 0));
		if (!SaveProgressInstance) { return; }
		SavedData = SaveProgressInstance->LevelSavedData;
	}
}

void AOpenWorld_BP::SavingEnemyData() {
	if (UGameplayStatics::DoesSaveGameExist("EnemyStatus", 0)) {
		auto SaveProgressInstance = Cast<USaveProgress>(UGameplayStatics::LoadGameFromSlot("EnemyStatus", 0));
		if (!SaveProgressInstance) { return; }
		SaveProgressInstance->LevelSavedData.Append(SavedData);
		UGameplayStatics::SaveGameToSlot(SaveProgressInstance, TEXT("EnemyStatus"), 0);
	}
}

void AOpenWorld_BP::SavePlayerStatus() {
	if (UGameplayStatics::DoesSaveGameExist("CheckPoint", 0)) {
		auto PlayerRef = GetWorld()->GetFirstPlayerController()->GetPawn();
		auto AimComponent = PlayerRef->FindComponentByClass<UTankAimingComponent>();
		auto SaveProgressInstance = Cast<USaveProgress>(UGameplayStatics::LoadGameFromSlot("CheckPoint", 0));
		FHitResult Hit;
		PlayerRef->SetActorLocation(SaveProgressInstance->PlayerPosition, false, &Hit, ETeleportType::TeleportPhysics);
		AimComponent->RetrievedSavedAmmo(SaveProgressInstance->TankAmmo, SaveProgressInstance->MachinegunAmmo, SaveProgressInstance->MaxMachinegunAmmo);
		Cast<ATank>(PlayerRef)->ReSpawn(SaveProgressInstance->PlayerLife);
		//
	}
}

void AOpenWorld_BP::BindingFunction(class ATankAIController* Enemy) {
	SavedData.Add(Enemy, Enemy->IsEnemyDead);
	SavingEnemyData();
}