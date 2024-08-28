#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimeBonusPoint.generated.h"

UCLASS()
class TIMERJAMGP8_API ATimeBonusPoint : public AActor
{
	GENERATED_BODY()

public:
	// Constructor
	ATimeBonusPoint();

protected:
	// Se llama cuando el juego comienza
	virtual void BeginPlay() override;

public:
	// Se llama cada frame
	virtual void Tick(float DeltaTime) override;

	// El TriggerBox para detectar cuando el jugador lo cruza
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UBoxComponent* TriggerBox;

	// Función para manejar la superposición con el jugador
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
