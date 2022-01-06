// Copyright Epic Games, Inc. All Rights Reserved.

#include "ArcanoidePlayerController.h"

AArcanoidePlayerController::AArcanoidePlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}
