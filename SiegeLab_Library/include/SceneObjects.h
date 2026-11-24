#pragma once
#include <vector>
#include <memory>
#include "GameEntity.h"
#include "ObjectPool.h"

class SceneObjects
{
public:
	template<typename ...Args>
	void createEntity(Args... args);
	const std::unique_ptr<GameEntity>& get(unsigned int id) const;
	void flushRemovals();

private:
	std::vector<std::unique_ptr<GameEntity>> gameEntities;
};

template<typename ...Args>
inline void SceneObjects::createEntity(Args... args)
{
}
