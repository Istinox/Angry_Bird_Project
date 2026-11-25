#pragma once
#include <concepts>
#include <utility>
#include <vector>
#include <memory>
#include <cstddef>
#include "GameEntity.h"
#include "ObjectPool.h"

// Vérifie si la sous classe T est bien dérivé de GameEntity.
template<typename T>
concept GameEntityType = std::derived_from<T, GameEntity>;

template<typename std::size_t MaxEntities>
class SceneObjects
{
public:
	template<GameEntityType T, typename... Args>
	requires std::constructible_from<T, Args...> // Vérifie si la sous-classe T est constructible avec les arguments Args données.
	EntityId createEntity(Args&&... args) {
		return objectPool.create(std::make_unique<T>(std::forward<Args>(args)...)); // "&&" = référence universelle.
	}

	GameEntity* get(EntityId id);
	const GameEntity* get(EntityId id) const;
	void flushRemovals();
	void markForRemovals(EntityId id) { pendingRemovals.push_back(id); }

private:
	ObjectPool<GameEntity, MaxEntities> objectPool;
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