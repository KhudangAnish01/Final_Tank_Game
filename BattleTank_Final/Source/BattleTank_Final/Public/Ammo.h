// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ammo.generated.h"

UCLASS()
class BATTLETANK_FINAL_API AAmmo : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAmmo();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnyWhere, Category = Ammo)
		class USphereComponent* Sphere1;//must include this for collision 

	UPROPERTY(VisibleAnyWhere, Category = Ammo)
		UStaticMeshComponent* Create;

	UFUNCTION()
		void GetAmmo(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	FString ammoname;
	FString FirstName;
	FString lastname;
};
