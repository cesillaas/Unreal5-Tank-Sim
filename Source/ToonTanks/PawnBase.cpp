
#include "PawnBase.h"
#include "Components/CapsuleComponent.h"
#include "Projectile.h"
#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"


APawnBase::APawnBase()
{
	PrimaryActorTick.bCanEverTick = true;

	capsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("capsuleComponent"));
	RootComponent = capsuleComponent;

	baseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("baseMesh"));
	baseMesh->SetupAttachment(RootComponent);

	turretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("turretMesh"));
	turretMesh->SetupAttachment(baseMesh);

	projectileSpawnComponent = CreateDefaultSubobject<USceneComponent>(TEXT("projectileSpawnComponent"));
	projectileSpawnComponent->SetupAttachment(turretMesh);

	healthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("healthComponent"));
}


void APawnBase::BeginPlay()
{
	Super::BeginPlay();
	
}


void APawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APawnBase::RotateTurret(const FVector& rotateTo, float DeltaTime)
{
	static FRotator lookRotation(0, 0, 0);
	lookRotation.Yaw = (rotateTo - turretMesh->GetComponentLocation()).Rotation().Yaw;
	turretMesh->SetWorldRotation(FMath::RInterpTo(turretMesh->GetComponentRotation(), lookRotation, DeltaTime, 25));
}

void APawnBase::Fire()
{
	GetWorld()->SpawnActor<AProjectile>(bulletClass, projectileSpawnComponent->GetComponentLocation(), projectileSpawnComponent->GetComponentRotation())->SetInstigator(this);
}

void APawnBase::HandleDeath()
{
	checkf(deathEffect, TEXT("deathEffect is nullptr"));
	UGameplayStatics::SpawnEmitterAtLocation(this, deathEffect, GetActorLocation(), GetActorRotation());

	checkf(deathSound, TEXT("deathSound is nullptr"));
	UGameplayStatics::PlaySoundAtLocation(this, deathSound, GetActorLocation());

	GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(deathCameraShakeClass);
}
