
#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "TankController.h"

ATank::ATank() : speed(200), rotateSpeed(100)
{
    springArmComponent = CreateDefaultSubobject<USpringArmComponent>("springArmComponent");
    springArmComponent->SetupAttachment(RootComponent);
    
    cameraComponent = CreateDefaultSubobject<UCameraComponent>("cameraComponent");
    cameraComponent->SetupAttachment(springArmComponent);
}

void ATank::HandleDeath()
{
    Super::HandleDeath();

    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
    GetController<ATankController>()->EnableAllControls(false);
    
    onTankDeath.Execute();
}
