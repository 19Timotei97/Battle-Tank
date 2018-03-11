// Copyright Bidila Timotei.


#include "TankAimingComponent.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Engine/World.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::BeginPlay()
{
	// This assures that the AI and the player tank fire at the same time,
	//after the initial reload time.
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::Initialize(UTankBarrel *BarrelToSet, UTankTurret *TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{	if(ProjLeft <= 0)
		AimState = EFiringState::OutOfAmmo;
	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
		AimState = EFiringState::Reloading;
	else if(IsBarrelMoving())
		AimState = EFiringState::Aiming;
	else
		AimState = EFiringState::Locked;
}

EFiringState UTankAimingComponent::GetFireState() const
{
	return AimState;
}

int32 UTankAimingComponent::getProjLeft() const
{
	return ProjLeft;
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel))
		return false;

	auto BarrelFwd = Barrel->GetForwardVector();

	return !BarrelFwd.Equals(AimDirection,0.01);
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel))
		return;

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (bHaveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel) || !ensure(Turret))
		return;

	// Get the diff between current barrel rotation and AD
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->ElevateBarrel(DeltaRotator.Pitch);
	if (FMath::Abs(DeltaRotator.Yaw) < 180)
		Turret->RotateTurret(DeltaRotator.Yaw);
	else
		Turret->RotateTurret(-DeltaRotator.Yaw);
}

void UTankAimingComponent::Fire()
{
	if (AimState == EFiringState::Locked || AimState == EFiringState::Aiming)
	{
		// Spawn a projectile at the socket location on the barrel
		if (!ensure(Barrel))
			return;

		if (!ensure(ProjectileBlueprint))
			return;

		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();

		ProjLeft--;
	}
}