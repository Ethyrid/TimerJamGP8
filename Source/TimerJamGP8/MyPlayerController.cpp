#include "MyPlayerController.h"
#include "Components/TextBlock.h"  // Incluye el TextBlock
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Blueprint/UserWidget.h"

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

			// Obtén la referencia al TextBlock dentro del widget TimerHUD
			TimeText = Cast<UTextBlock>(TimerWidgetInstance->GetWidgetFromName(TEXT("TimeText")));

			// Muestra el tiempo inicial
			UpdateTimerDisplay();
		}
	}
}

void AMyPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	// Aquí podrías realizar otras actualizaciones, si es necesario
}

void AMyPlayerController::UpdateTimer()
{
	if (RemainingTime > 0)
	{
		--RemainingTime;
		UpdateTimerDisplay();  // Actualiza el tiempo en pantalla cada segundo
	}
	else
	{
		HandleDefeat();
	}
}

void AMyPlayerController::UpdateTimerDisplay()
{
	if (TimeText)
	{
		int32 Minutes = RemainingTime / 60;
		int32 Seconds = RemainingTime % 60;
		TimeText->SetText(FText::FromString(FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds)));
	}
}

void AMyPlayerController::HandleVictory()
{
	UGameplayStatics::OpenLevel(this, FName("VictoryMap"));
}

void AMyPlayerController::HandleDefeat()
{
	GetWorld()->GetTimerManager().ClearTimer(CountdownTimerHandle);
	UGameplayStatics::OpenLevel(this, FName("GameOverMap"));
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
