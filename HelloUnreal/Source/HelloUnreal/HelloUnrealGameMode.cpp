// Copyright Epic Games, Inc. All Rights Reserved.

#include "HelloUnrealGameMode.h"
#include "HelloUnrealPlayerController.h"
#include "HelloUnrealCharacter.h"
#include "UObject/ConstructorHelpers.h"

AHelloUnrealGameMode::AHelloUnrealGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AHelloUnrealPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}