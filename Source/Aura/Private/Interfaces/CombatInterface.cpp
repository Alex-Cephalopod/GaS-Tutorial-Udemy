// Copyright Cephalo-Alex


#include "Interfaces/CombatInterface.h"

// Add default functionality here for any ICombatInterface functions that are not pure virtual.

int32 ICombatInterface::GetPlayerLevel()
{
	return 0;
}

FVector ICombatInterface::GetCombatSocketLocation()
{
	return FVector();
}

void ICombatInterface::UpdateWarpTarget(FVector& FacingTarget)
{
	return;
}
