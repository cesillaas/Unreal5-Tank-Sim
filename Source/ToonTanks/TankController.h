
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankController.generated.h"

class UInputAction;
class UInputMappingContext;
struct FInputActionValue;
class ATank;

UCLASS()
class TOONTANKS_API ATankController : public APlayerController
{
	GENERATED_BODY()

public:

	ATankController();

	void SetupInputComponent() override;

	virtual void Tick(float DeltaTime) override;

	void EnableAllControls(bool enable);

protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
	UInputAction* walkAction;

	UPROPERTY(EditAnywhere)
	UInputAction* turnAction;

	UPROPERTY(EditAnywhere)
	UInputAction* shootAction;

	UPROPERTY(EditAnywhere)
	UInputMappingContext* mapping;

	ATank* tankControlled;

	void HandleTurretRotation(float DeltaTime);

	void HandleWalk(const FInputActionValue& inputActionValue);
	void HandleTurn(const FInputActionValue& inputActionValue);
	void HandleShoot();
};
