// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnPoint.h"
#include "SprungWheel.h"
#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void  UTankTrack::SetThrottle(float Throttle)
{
	auto CurrentThrottle = FMath::Clamp<float>(Throttle, -1, 1);
	DriveTrack(CurrentThrottle);
}

void UTankTrack::DriveTrack(float CurrentThrottle)
{
	auto ForceApplied = CurrentThrottle * TrackMaxDrivingForce;//get forward get forward value

	auto Wheels = GetWheels();

	auto ForcePerWheel = ForceApplied/ Wheels.Num();

	for (ASprungWheel* Wheel : Wheels) {
		Wheel->AddDrivingForce(ForcePerWheel);
	}
}

TArray<ASprungWheel*> UTankTrack::GetWheels() const{

	TArray <ASprungWheel*> resultarray;

	TArray<USceneComponent*>Children;

	GetChildrenComponents(true, Children);//savai child ayo of TankTrack

	for (USceneComponent* Child : Children) {
		auto SpawnChildPoint = Cast<USpawnPoint>(Child);//uscenecomponent to Uspawnpoint
		if (!SpawnChildPoint)continue;
		AActor* SpawnChild = SpawnChildPoint->GetSpawnActor();//getting spawn actor in USpawnPoint to determine Springwheel out of many
		if (!SpawnChild)continue;
		auto SpringWheel = Cast<ASprungWheel>(SpawnChild);//spawnpoint to spring;
		if (!SpringWheel)continue;
		resultarray.Add(SpringWheel);
	}
	return resultarray;
}




