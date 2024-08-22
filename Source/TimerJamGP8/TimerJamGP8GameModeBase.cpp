// Copyright Epic Games, Inc. All Rights Reserved.


#include "TimerJamGP8GameModeBase.h"
#include "MyPlayerController.h"

AMyGameModeBase::AMyGameModeBase()
{
	// Configura el PlayerControllerClass para utilizar tu PlayerController personalizado
	PlayerControllerClass = AMyPlayerController::StaticClass();
}
