#include "SceneObjects.h"
#include "ObjectPool.h"

const std::unique_ptr<GameEntity>& SceneObjects::get(unsigned int id) const
{
	return gameEntities[id];
}

void SceneObjects::flushRemovals()
{
}
