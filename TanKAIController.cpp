// Copyright Bidila Timotei 2017.


#include "TanKAIController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "Projectile.h"
#include "Tank.h" // Used for method impl of OnDeath
// Depends on movement comp via pathfinding system

void ATanKAIController::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATanKAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		auto PossesedTank = Cast<ATank>(InPawn);
		if (!ensure(PossesedTank))
			return;

		// Linking the method OnTankDeath to the Possessed Tank
		PossesedTank->OnDeath.AddUniqueDynamic(this, &ATanKAIController::OnTankDeath);
	
	}
}

void ATanKAIController::OnTankDeath()
{
	if (!GetPawn())
		return;

	GetPawn()->DetachFromControllerPendingDestroy();
}

void ATanKAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	auto ControlledTank = GetPawn();

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	
	if (!ensure(PlayerTank && ControlledTank))
		return;
	
		
	// Move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius);

	// Aim towards the player
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	AimingComponent->AimAt(PlayerTank->GetTargetLocation());

	if(AimingComponent->GetFireState() == EFiringState::Locked)
		AimingComponent->Fire(); // TODO  limit firing rate
	
}










