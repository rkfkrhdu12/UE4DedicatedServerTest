// Copyright Epic Games, Inc. All Rights Reserved.

#include "ServerTestProjectGameMode.h"
#include "ServerTestProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AServerTestProjectGameMode::AServerTestProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
