
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StartWidget.generated.h"


UCLASS(Abstract)
class TOONTANKS_API UStartWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* startText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* countdownText;
};
