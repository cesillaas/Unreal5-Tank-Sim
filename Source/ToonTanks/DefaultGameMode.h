
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DefaultGameMode.generated.h"

class UStartWidget;
class ATankController;
class ATurret;

UCLASS()
class TOONTANKS_API ADefaultGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	ADefaultGameMode();
	virtual void Tick(float DeltaTime);

protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY(EditDefaultsOnly)
	float countdownTime;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UStartWidget> startWidgetClass;

	UPROPERTY()                // this is to stop the garbage collector from freeing memory 
	UStartWidget* startWidget; // after removing the widget from the parent, it frees memory after sometime

	ATankController* tankController;
	FTimerHandle countdownTimerHandle;

	int32 numberOfTurrets;

	void OnCountdownEnd();
	void HandleDelegateBinding();
	void HandleEndWidget(const FString& text);
	
	UFUNCTION()
	void OnTankDeath();
	
	UFUNCTION()
	void OnTurretDeath();

};
