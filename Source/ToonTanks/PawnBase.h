
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnBase.generated.h"

UCLASS(Abstract)
class TOONTANKS_API APawnBase : public APawn
{
	GENERATED_BODY()

public:
	
	APawnBase();

protected:
	
	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;
	virtual void HandleDeath();
	void RotateTurret(const FVector& rotateTo, float DeltaTime);
	void Fire();
	
private:

	UPROPERTY(VisibleAnywhere)
	class UCapsuleComponent* capsuleComponent;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* baseMesh;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* turretMesh;
	
	UPROPERTY(VisibleAnywhere)
	USceneComponent* projectileSpawnComponent;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AProjectile> bulletClass;

	UPROPERTY(VisibleAnywhere)
	class UHealthComponent* healthComponent;

	UPROPERTY(EditDefaultsOnly)
	class UParticleSystem* deathEffect;

	UPROPERTY(EditDefaultsOnly)
	class USoundBase* deathSound;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCameraShakeBase> deathCameraShakeClass;
};
