
#include "Turret.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

ATurret::ATurret() : fireRange(300), fireCooldown(2), tank(nullptr) 
{

}

void ATurret::BeginPlay()
{
    Super::BeginPlay();
    tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    GetWorld()->GetTimerManager().SetTimer(fireTimerHandle, this, &ATurret::HandleFire, fireCooldown, true);
}

void ATurret::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (IsSightClear()) return;
    RotateTurret(tank->GetActorLocation(), DeltaTime);
}

void ATurret::HandleFire()
{
    if (IsSightClear()) return;
    Fire();
}

bool ATurret::IsSightClear()
{
    return tank->IsHidden() || FVector::Dist(GetActorLocation(), tank->GetActorLocation()) > fireRange;
}

void ATurret::HandleDeath()
{
    Super::HandleDeath();
    onTurretDeath.Execute();
    GetWorld()->DestroyActor(this);
}
