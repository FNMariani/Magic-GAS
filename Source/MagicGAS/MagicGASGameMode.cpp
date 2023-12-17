// Copyright Epic Games, Inc. All Rights Reserved.

#include "MagicGASGameMode.h"
#include "MagicGASCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMagicGASGameMode::AMagicGASGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
