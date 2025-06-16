
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"


UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AProjectile();

protected:

	virtual void BeginPlay() override;

public:	
	
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditDefaultsOnly)
	float speed;

	UPROPERTY(EditDefaultsOnly)
	float damage;

	UPROPERTY(EditDefaultsOnly)
	class UParticleSystem* hitEffect;

	UPROPERTY(EditDefaultsOnly)
	class USoundBase* hitSound;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCameraShakeBase> hitCameraShakeClass;

	UFUNCTION()
	void OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
