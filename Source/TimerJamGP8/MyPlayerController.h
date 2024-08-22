#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

UCLASS()
class TIMERJAMGP8_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMyPlayerController();

protected:
	// Se llama cuando el juego comienza
	virtual void BeginPlay() override;

private:
	// Método para iniciar el temporizador
	void IniciarTemporizador();

	// Método que se llama en cada tick del temporizador
	void ActualizarTemporizador();

	// Controlador del temporizador
	FTimerHandle TimerHandle;

	// Variable que mantiene el tiempo restante
	int32 TiempoRestante;
};