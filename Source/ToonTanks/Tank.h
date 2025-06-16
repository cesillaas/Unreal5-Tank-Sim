
#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "Tank.generated.h"

DECLARE_DELEGATE(FTankDeathSignature)


UCLASS()
class TOONTANKS_API ATank : public APawnBase
{
	GENERATED_BODY()

public:

	ATank();

	inline float GetSpeed() const { return speed; }
	inline float GetRotateSpeed() const { return rotateSpeed; }

	FTankDeathSignature onTankDeath;

private:

	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* springArmComponent;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* cameraComponent;

	UPROPERTY(EditDefaultsOnly)
	float speed;
	
	UPROPERTY(EditDefaultsOnly)
	float rotateSpeed;

	void HandleDeath() override;
};
