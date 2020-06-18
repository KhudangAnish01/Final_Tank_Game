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
		if (UGameplayStatics::DoesSaveGameExist("EnemyStatus", 1)) {
			UGameplayStatics::DeleteGameInSlot("EnemyStatus", 1);
		}
		if (UGameplayStatics::DoesSaveGameExist("CheckPoint", 0)) {
			UGameplayStatics::DeleteGameInSlot("CheckPoint", 0);
		}
	}

	if (UGameplayStatics::DoesSaveGameExist("CheckPoint", 0)) {
		LoadPlayerStatus();//saving enemy Status
	}

	AMyGameStateBase* const MyGameState = GetWorld() != NULL ? GetWorld()->GetGameState<AMyGameStateBase>() : NULL;
	MyGameState->EnemyDestroyed.AddDynamic(this, &AOpenWorld_BP::BindingFunction);
	//GetAllAcctorOfClass(Getting All AI ref)
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATankAIController::StaticClass(), FoundActors);

	for (auto& AIRef : FoundActors) {
		auto Ref = Cast<ATankAIController>(AIRef);
		for (auto& SaveGameRef : GameInstanceRef->SaveGameInstance->LevelSavedDatas) {
			if ((Ref->GetName()== SaveGameRef)) {
				Ref->IsEnemyDead = true;
				Ref->Update();
				UE_LOG(LogTemp, Warning, TEXT("hello"));
			}
		}
	}
}

void AOpenWorld_BP::LoadPlayerStatus() {
		auto GameInstanceRef = Cast<UMenuSwitchGameInstance>(GetWorld()->GetGameInstance());
		if (!GameInstanceRef) { return; }
		GameInstanceRef->LoadPlayerStatus();
}

void AOpenWorld_BP::BindingFunction(class ATankAIController* Enemy) {
	auto GameInstanceRef = Cast<UMenuSwitchGameInstance>(GetGameInstance());
	FAsyncSaveGameToSlotDelegate SavedDelegate;
	SavedDelegate.BindUObject(this, &AOpenWorld_BP::SaveGameDelegateFunction);
	GameInstanceRef->SaveGameInstance->LevelSavedDatas.Add(Enemy->GetName());
	UGameplayStatics::AsyncSaveGameToSlot(GameInstanceRef->SaveGameInstance, TEXT("CheckPoint"), 0, SavedDelegate);
}

void AOpenWorld_BP::SaveGameDelegateFunction(const FString& SlotName, const int32 UserIndex, bool bSuccess) {
}