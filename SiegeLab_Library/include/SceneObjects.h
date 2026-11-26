#pragma once

#include <concepts>
#include <cstddef>
#include <utility>
#include <vector>

#include "GameEntity.h"
#include "ObjectPool.h"
#include "Physics/PhysicsRegistration.h"
#include "Physics/PhysicsWorld.h"

// Vérifie si la sous classe T est bien dérivé de GameEntity.
template<typename T>
concept GameEntityType = std::derived_from<T, GameEntity>;

template<std::size_t MaxEntities>
class SceneObjects
{
public:
	template<GameEntityType T, typename... Args>
		requires std::constructible_from<T, Args...> // Vérifie si la sous-classe T est constructible avec les arguments Args données.
	EntityId createEntity(Args&&... args) {
		return objectPool.template create<T>(std::forward<Args>(args)...); // "&&" = référence universelle.
	}

	GameEntity* get(EntityId id);
	const GameEntity* get(EntityId id) const;
	void flushRemovals();
	void markForRemovals(EntityId id) { pendingRemovals.push_back(id); }

private:
	ObjectPool<GameEntity, MaxEntities> objectPool;
	PhysicsWorld physicWorld;
	std::vector<EntityId> pendingRemovals;
};

template<std::size_t MaxEntities>
inline const GameEntity* SceneObjects<MaxEntities>::get(EntityId id) const
{
	return objectPool.get(id);
}

template<std::size_t MaxEntities>
inline GameEntity* SceneObjects<MaxEntities>::get(EntityId id)
{
	return objectPool.get(id);
}

template<std::size_t MaxEntities>
inline void SceneObjects<MaxEntities>::flushRemovals()
{
	for (EntityId id : pendingRemovals) {
		objectPool.destroy(id);
	}

	pendingRemovals.clear();
}