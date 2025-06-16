
#include "HealthComponent.h"
#include "PawnBase.h"


UHealthComponent::UHealthComponent() : maxHealth(100)
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	health = maxHealth;	
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnTakeDamage);
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHealthComponent::OnTakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage < health)
	{
		health -= Damage;
	}

	else
	{
		health = 0;
		if (APawnBase* pawn = Cast<APawnBase>(GetOwner()))
		{
			pawn->HandleDeath();
		}
	}
}
