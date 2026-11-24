#pragma once
#include <vector>
#include <memory>
#include "GameEntity.h"
#include "ObjectPool.h"

class SceneObjects
{
public:
	template<typename T>
	void createEntity(T);
	void get(unsigned int id);
	void flushRemovals();

private:
	std::vector<std::unique_ptr<GameEntity>> gameEntities;
};

template<typename T>
inline void SceneObjects::createEntity(T)
{
}
