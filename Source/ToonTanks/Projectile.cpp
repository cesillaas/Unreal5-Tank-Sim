
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "HealthComponent.h"
#include "GameFramework/DamageType.h"


AProjectile::AProjectile() : speed(1000), damage(50)
{

	PrimaryActorTick.bCanEverTick = true;

}


void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	GetComponentByClass<UStaticMeshComponent>()->OnComponentHit.AddDynamic(this, &AProjectile::OnComponentHit);
}


void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AddActorLocalOffset(FVector(speed * DeltaTime, 0, 0), true);
}

void AProjectile::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor == GetInstigator()) return;
	
	if (OtherActor->GetComponentByClass<UHealthComponent>())
	{
		UGameplayStatics::ApplyDamage(OtherActor, damage, GetInstigatorController(), this, UDamageType::StaticClass());
	}

	checkf(hitEffect, TEXT("hitEffect is nullptr"));
	UGameplayStatics::SpawnEmitterAtLocation(this, hitEffect, GetActorLocation(), GetActorRotation());

	checkf(hitSound, TEXT("hitSound is nullptr"));
	UGameplayStatics::PlaySoundAtLocation(this, hitSound, GetActorLocation());

	UWorld* world = GetWorld();

	world->GetFirstPlayerController()->ClientStartCameraShake(hitCameraShakeClass);
	world->DestroyActor(this);
}
