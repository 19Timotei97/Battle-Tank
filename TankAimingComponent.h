// Copyright Bidila Timotei.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

// Foward declaration
class UTankBarrel; 
class UTankTurret;
class AProjectile;

// Used for the state of the aiming
UENUM()
enum class EFiringState: uint8
{
	Reloading,
	Aiming,
	Locked,
	OutOfAmmo
};

// Holds barrel's properties and elevates method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel *BarrelToSet, UTankTurret *TurretToSet);

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Fire")
	void Fire();

	EFiringState GetFireState() const;

	UFUNCTION(BlueprintCallable, Category = "Fire")
	int32 getProjLeft() const;

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState AimState = EFiringState::Reloading;

private:
	// Sets default values for this component's properties
	UTankAimingComponent();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	bool IsBarrelMoving();

	void MoveBarrelTowards(FVector AimDirection);

	FVector AimDirection;

	//Local barrel ref for spawing projectile
	UTankBarrel* Barrel = nullptr;

	UTankTurret* Turret = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint; /// Or, more general, UClass*

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float ReloadTimeInSeconds = 3.0;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	int32 ProjLeft = 3;

	double LastFireTime = 0;

	

};
