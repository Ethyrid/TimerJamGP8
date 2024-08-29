#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "MyPlayerController.generated.h"

UCLASS()
class TIMERJAMGP8_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMyPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	// Manejador del temporizador
	FTimerHandle CountdownTimerHandle;

	// Tiempo restante en segundos
	int32 RemainingTime;

	// Puntos recolectados
	int32 PointsCollected;

	// Tiempo inicial del temporizador
	UPROPERTY(EditAnywhere, Category = "Timer")
		int32 InitialTime = 150;

	// Tiempo extra al pasar por un punto
	UPROPERTY(EditAnywhere, Category = "Timer")
		int32 TimeBonus = 10;

	// Referencia al Blueprint del widget TimerHUD
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
		TSubclassOf<UUserWidget> TimerWidgetClass;

	// Instancia del widget TimerHUD
	UPROPERTY()
		UUserWidget* TimerWidgetInstance;

	// Referencia al TextBlock dentro del TimerHUD para mostrar el tiempo
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* TimeText;

	// Actualiza el temporizador
	void UpdateTimer();

	// Actualiza el texto del temporizador en la pantalla
	void UpdateTimerDisplay();

	// Maneja la victoria
	void HandleVictory();

	// Maneja la derrota
	void HandleDefeat();

public:
	// Añade un bono de tiempo
	UFUNCTION()
		void AddTimeBonus();

	// Devuelve el tiempo restante
	UFUNCTION(BlueprintCallable, Category = "Timer")
		int32 GetRemainingTime() const;
};
