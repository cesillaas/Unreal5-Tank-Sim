
#include "TankController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Tank.h"

ATankController::ATankController() : tankControlled(nullptr)
{

}


void ATankController::SetupInputComponent()
{
    Super::SetupInputComponent();

    UEnhancedInputComponent* enhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
    checkf(enhancedInputComponent, TEXT("could not cast to UEnhancedInputComponent"));

    checkf(walkAction, TEXT("walkAction is nullptr"));
    enhancedInputComponent->BindAction(walkAction, ETriggerEvent::Triggered, this, &ATankController::HandleWalk);

    checkf(turnAction, TEXT("turnAction is nullptr"));
    enhancedInputComponent->BindAction(turnAction, ETriggerEvent::Triggered, this, &ATankController::HandleTurn);

    checkf(shootAction, TEXT("shootAction is nullptr"));
    enhancedInputComponent->BindAction(shootAction, ETriggerEvent::Triggered, this, &ATankController::HandleShoot);

    UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
    checkf(subsystem, TEXT("could not get the UEnhancedInputLocalPlayerSubsystem"));

    subsystem->ClearAllMappings();
    subsystem->AddMappingContext(mapping, 0);
}

void ATankController::BeginPlay()
{
    Super::BeginPlay();
    tankControlled = Cast<ATank>(GetPawn());
}

void ATankController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    HandleTurretRotation(DeltaTime);
}

void ATankController::HandleTurretRotation(float DeltaTime)
{
    static FHitResult hitResult;
    GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, hitResult);
    tankControlled->RotateTurret(hitResult.ImpactPoint, DeltaTime);
}


void ATankController::HandleWalk(const FInputActionValue& inputActionValue)
{
    tankControlled->AddActorLocalOffset(inputActionValue.Get<FVector>() * tankControlled->GetSpeed() * GetWorld()->GetDeltaSeconds(), true);
}

void ATankController::HandleTurn(const FInputActionValue& inputActionValue)
{
    tankControlled->AddActorLocalRotation(FRotator(0, inputActionValue.Get<FVector>().X, 0) * tankControlled->GetRotateSpeed() * GetWorld()->GetDeltaSeconds(), true);
}

void ATankController::HandleShoot()
{
    tankControlled->Fire();
}

void ATankController::EnableAllControls(bool enable)
{
    enable ? EnableInput(this) : DisableInput(this);
    SetActorTickEnabled(enable);
    bShowMouseCursor = enable;
}
