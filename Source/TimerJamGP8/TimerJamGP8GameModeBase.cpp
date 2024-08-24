// Copyright Epic Games, Inc. All Rights Reserved.


#include "TimerJamGP8GameModeBase.h"
#include "MyPlayerController.h"

AMyGameModeBase::AMyGameModeBase()
{
	// PlayerControllerClass = mi PlayerController personalizado
	PlayerControllerClass = AMyPlayerController::StaticClass();
}
