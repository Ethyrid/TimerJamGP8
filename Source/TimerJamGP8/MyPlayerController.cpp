#include "MyPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Blueprint/UserWidget.h"  // Asegúrate de incluir esto para trabajar con UUserWidget

AMyPlayerController::AMyPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	RemainingTime = InitialTime;
	PointsCollected = 0;
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(CountdownTimerHandle, this, &AMyPlayerController::UpdateTimer, 1.0f, true);

	if (TimerWidgetClass != nullptr)
	{
		TimerWidgetInstance = CreateWidget<UUserWidget>(this, TimerWidgetClass);
		if (TimerWidgetInstance != nullptr)
		{
			TimerWidgetInstance->AddToViewport();
		}
	}
}

void AMyPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (TimerWidgetInstance)
	{
		// Puedes actualizar el widget con el tiempo restante aquí si es necesario
	}
}

void AMyPlayerController::UpdateTimer()
{
	if (RemainingTime > 0)
	{
		--RemainingTime;
		// Actualizar el widget aquí si es necesario
	}
	else
	{
		HandleDefeat();
	}
}

void AMyPlayerController::HandleVictory()
{
	UGameplayStatics::OpenLevel(this, FName("VictoryMap"));  // Cambia al mapa de victoria
}

void AMyPlayerController::HandleDefeat()
{
	GetWorld()->GetTimerManager().ClearTimer(CountdownTimerHandle);
	UGameplayStatics::OpenLevel(this, FName("GameOverMap"));  // Cambia al mapa de derrota
}

void AMyPlayerController::AddTimeBonus()
{
	RemainingTime += TimeBonus;
	PointsCollected++;

	if (PointsCollected >= 10)
	{
		HandleVictory();
	}
}

int32 AMyPlayerController::GetRemainingTime() const
{
	return RemainingTime;
}
