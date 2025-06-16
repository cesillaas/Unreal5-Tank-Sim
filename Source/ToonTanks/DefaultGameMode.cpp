
#include "DefaultGameMode.h"
#include "TankController.h"
#include "Kismet/GameplayStatics.h"
#include "StartWidget.h"
#include "Components/TextBlock.h"
#include "Tank.h"
#include "Turret.h"


ADefaultGameMode::ADefaultGameMode() : countdownTime(3), numberOfTurrets(0)
{
    PrimaryActorTick.bCanEverTick = true;
}

void ADefaultGameMode::BeginPlay()
{
    tankController = UGameplayStatics::GetPlayerPawn(this, 0)->GetController<ATankController>();
    startWidget = CreateWidget<UStartWidget>(tankController, startWidgetClass);
    startWidget->AddToViewport();

    tankController->EnableAllControls(false);
    GetWorld()->GetTimerManager().SetTimer(countdownTimerHandle, this, &ADefaultGameMode::OnCountdownEnd, countdownTime, false);

    HandleDelegateBinding();
}

void ADefaultGameMode::Tick(float DeltaTime)
{
    if (GetWorld()->GetTimerManager().TimerExists(countdownTimerHandle))
    {
        startWidget->countdownText->SetText(FText::FromString(FString::Printf(TEXT("%d"), FMath::CeilToInt32(GetWorld()->GetTimerManager().GetTimerRemaining(countdownTimerHandle)))));
    }
}

void ADefaultGameMode::OnCountdownEnd()
{
    startWidget->RemoveFromParent();
    tankController->EnableAllControls(true);
}

void ADefaultGameMode::OnTankDeath()
{
    HandleEndWidget(TEXT("You lost"));
}

void ADefaultGameMode::OnTurretDeath()
{
    if (--numberOfTurrets) return;
    HandleEndWidget(TEXT("You won!"));
}

void ADefaultGameMode::HandleDelegateBinding()
{
    Cast<ATank>(tankController->GetPawn())->onTankDeath.BindUObject(this, &ADefaultGameMode::OnTankDeath);
    TArray<AActor*> turrets;
    UGameplayStatics::GetAllActorsOfClass(this, ATurret::StaticClass(), turrets);
    numberOfTurrets = turrets.Num();
    for (AActor* turret : turrets)
    {
        Cast<ATurret>(turret)->onTurretDeath.BindUObject(this, &ADefaultGameMode::OnTurretDeath);
    }
}

void ADefaultGameMode::HandleEndWidget(const FString& text)
{
    if (startWidget->IsInViewport()) return;
    startWidget->AddToViewport();
    startWidget->countdownText->RemoveFromParent();
    startWidget->startText->SetText(FText::FromString(text));
}
