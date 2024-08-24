#include "MyPlayerController.h"
#include "TimerManager.h"  // Maneja los temporizadores

AMyPlayerController::AMyPlayerController()
{
	// Inicia el tiempo restante (10 segundos en este caso)
	TiempoRestante = 10;
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Metodo para iniciar el temporizador
	IniciarTemporizador();
}

void AMyPlayerController::IniciarTemporizador()
{
	// Verifica que el mundo sea válido antes de intentar obtener el TimerManager
	if (GetWorld())
	{
		// Configura el temporizador para que llame a ActualizarTemporizador cada segundo
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AMyPlayerController::ActualizarTemporizador, 1.0f, true);
	}
}

void AMyPlayerController::ActualizarTemporizador()
{
	// Resta 1 al tiempo restante
	TiempoRestante--;

	// Imprime el tiempo restante en la consola
	UE_LOG(LogTemp, Warning, TEXT("Tiempo restante: %d"), TiempoRestante);

	// Si el tiempo restante es menor o igual a 0, el temporizador se para
	if (TiempoRestante <= 0)
	{
		// Detiene el temporizador
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);

		// Imprime un mensaje indicando que el tiempo ha terminado
		UE_LOG(LogTemp, Warning, TEXT("¡Se acabó el tiempo!"));
	}
}