//	Copyright Bidila Timotei.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack *LeftTankTrackToSet, UTankTrack *RightTankTrackToSet)
{
	
	LeftTrack = LeftTankTrackToSet;
	RightTrack = RightTankTrackToSet;

}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	// Because I'm overloading the method, I don't need to call Super();

	auto TankXAxis = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIPath = MoveVelocity.GetSafeNormal();

	auto ForwardThrow = FVector::DotProduct(TankXAxis, AIPath);
	IntendMoveForward(ForwardThrow);

	auto RightThrow = FVector::CrossProduct(TankXAxis, AIPath).Z;
	IntendTurnRight(RightThrow);
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}
