
#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "Turret.generated.h"


DECLARE_DELEGATE(FTurretDeathSignature)


UCLASS()
class TOONTANKS_API ATurret : public APawnBase
{
	GENERATED_BODY()

public:

	ATurret();
	virtual void Tick(float DeltaTime) override;

	FTurretDeathSignature onTurretDeath;

protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
	float fireRange;
	
	UPROPERTY(EditAnywhere)
	float fireCooldown;

	class ATank* tank;

	FTimerHandle fireTimerHandle;

	UFUNCTION()
	void HandleFire();

	bool IsSightClear();

	void HandleDeath() override;
};
