// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	ApplySidewaysForce();
	DriveTrack(CurrentThrottle);
	CurrentThrottle = 0;
}

void UTankTrack::ApplySidewaysForce()
{
	//each tick it place opposite force to stop slippage if angle between GetRightVector and GetComponentVelocity is 0 and 180 i.e(cosine law)
	auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	//required acceleration
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto CorrectioAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();//here a=(change of velocity/change of time).We multiply it with getrightvector cause tank need to move toward right

	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	//applied sideway force
	auto SideWayForce = TankRoot->GetMass() * CorrectioAcceleration / 2;
	TankRoot->AddForce(SideWayForce);
}

void  UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}

void UTankTrack::DriveTrack(float Throttle)
{
	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;//get forward get forward value
	auto ForceLocation = GetComponentLocation();
	//we must use tankroot to apply force and must be uprimitivecomponent.
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}



