// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "TankMovementComponent.h"

void UTankMovementComponent::Inialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)//AI Movement
{
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto MoveVelocityString = MoveVelocity.GetSafeNormal();

	auto ForwardThrow = FVector::DotProduct(TankForward, MoveVelocityString);
	IntendMoveForward(ForwardThrow);
	auto RightThrow= FVector::CrossProduct(TankForward, MoveVelocityString).Z;
	IntendTurnRight(RightThrow);
	//UE_LOG(LogTemp, Warning, TEXT("%s vectoring to %s"), *TankName, *MoveVelocityString)
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }//here we make two value as 1, 1 cause we need to move only forwrd
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }///here 1,-1 cause for turn left right one wheel must move forward another backward
		LeftTrack->SetThrottle(-Throw);
		RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::TrackReference() {
	if (!ensure(LeftTrack && RightTrack)) { return; }
	LeftTrack->DestroySpawnPoint();
	RightTrack->DestroySpawnPoint();
}