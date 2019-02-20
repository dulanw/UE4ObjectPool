# UE4ObjectPool
AActor and UObject pool (no pool manager) these are sub-classes of UObjects, so will need to be created using 
 ``` MyActorPool = NewObject<UActorPool>(this); ``` 
 UActorPool for actors and UObjectPool for anything else, this is because actors are spawned into the world.
 Make sure to implement the ActorInterface for both UObjects and AActors, you will need to call AddActorToPool from inside the PooledObject to deactivate it and make it available to be used again. 
