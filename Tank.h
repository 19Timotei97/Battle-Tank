// Copyright Bidila Timotei.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Delegates/Delegate.h"
#include "Tank.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// The method called when an actor is dealt damage
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent,class AController * EventInstigator,AActor * DamageCauser) override;

	UFUNCTION(BlueprintPure, Category = "Health")
	float getHealthPercent() const;

	FTankDelegate OnDeath;

private:
	// Sets default values for this pawn's properties
	ATank();

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth;	// Initialized in BeginPlay
};
