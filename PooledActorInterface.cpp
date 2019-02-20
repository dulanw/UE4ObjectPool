// Copyright 2019 Dulan Wettasinghe. All Rights Reserved.

#include "PooledActorInterface.h"

// Add default functionality here for any IPooledActorInterface functions that are not pure virtual.

bool IPooledActorInterface::InitPooledActor(UActorPool* InPool)
{
	if (!InPool || ParentPool)
		return false;

	ParentPool = InPool;
	return true;
}
