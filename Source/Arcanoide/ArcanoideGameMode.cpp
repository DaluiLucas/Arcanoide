// Copyright Epic Games, Inc. All Rights Reserved.

#include "ArcanoideGameMode.h"
#include "ArcanoidePlayerController.h"
#include "ArcanoidePawn.h"

AArcanoideGameMode::AArcanoideGameMode()
{
	// no pawn by default
	DefaultPawnClass = AArcanoidePawn::StaticClass();
	// use our own player controller class
	PlayerControllerClass = AArcanoidePlayerController::StaticClass();
}
