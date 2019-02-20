// Copyright 2019 Dulan Wettasinghe. All Rights Reserved.

#include "ActorPool.h"
#include "GameFramework/Actor.h"
#include "Utility/PooledActorInterface.h"

AActor* UActorPool::GetActorFromPool()
{
	if (!ObjectPoolClass)
		return nullptr;

	if (InActiveObjects.Num() > 0)
	{
		auto newobject = InActiveObjects.Pop();
		ActiveObjects.Add(newobject);

		return newobject;
	}
	else
	{
		if (bExpandPool)
		{
			UWorld* MyWorld = GetWorld();

			if (!MyWorld)
				return nullptr;

			AActor* newObject = MyWorld->SpawnActor<AActor>(ObjectPoolClass, FVector::ZeroVector, FRotator::ZeroRotator);
			if (newObject)
			{
				InActiveObjects.Add(newObject);

				IPooledActorInterface* newInterface = Cast<IPooledActorInterface>(newObject);
				if (newInterface)
					newInterface->InitPooledActor(this);

				return newObject;
			}
			else
				return nullptr;

		}
		else
		{
			return nullptr;
		}

	}
}

bool UActorPool::AddActorToPool(AActor* InObject)
{
	if (!InObject || ActiveObjects.Num() <= 0)
		return false;

	auto newPointer = ActiveObjects.Find(InObject);
	if (newPointer)
	{
		ActiveObjects.Remove(InObject);
		InActiveObjects.Add(InObject);
		return true;
	}
	else
	{
		return false;
	}

}

bool UActorPool::InitPool(UClass* InObjectPoolClass, uint32 InPoolSize, bool InbExpandPool)
{
	/*return if we have already called InitPool once before*/
	if (ObjectPoolClass)
		return false;

	ObjectPoolClass = InObjectPoolClass;
	bExpandPool = InbExpandPool;

	UWorld* MyWorld = GetWorld();
	if (!MyWorld)
		return false;

	for (uint32 i = 0; i < InPoolSize; i++)
	{
		AActor* newObject = MyWorld->SpawnActor<AActor>(ObjectPoolClass, FVector::ZeroVector, FRotator::ZeroRotator);

		if (newObject)
		{
			UE_LOG(LogTemp, Warning, TEXT("added %d"), i);
			InActiveObjects.Add(newObject);

			IPooledActorInterface* newInterface = Cast<IPooledActorInterface>(newObject);
			if (newInterface)
				newInterface->InitPooledActor(this);
		}
		else
			return false;
	}

	return true;
}

