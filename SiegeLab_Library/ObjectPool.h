#pragma once
#include <vector>
#include <stdexcept>
#include <functional>
#include "EntityId.h"

template<typename T, std::size_t Capacity>
class ObjectPool
{
public:
	ObjectPool() { entities.reserve(Capacity); }

	EntityId create(T args);
	void get(const EntityId id);
	void destroy(EntityId& id);
	void forEach(std::function<T>&& func);
	void clear();

	bool isSlotValid(int id);
	bool isGenValid(const EntityId id);

private:
	std::vector<EntityId> entities;
	int currentGeneration = 0;
};

template<typename T, std::size_t Capacity>
inline EntityId ObjectPool<T, Capacity>::create(T args)
{
	if (entities.size() == Capacity) {
		return;
	}

	EntityId entity {
		entity.slot = 0,
		entity.generation = 0
	};

	for (size_t id = 0; id < Capacity; id++)
	{
		if (isSlotValid(id))
		{
			entity.slot = id;
			entity.generation = currentGeneration;

			return entity;
		}
	}

	throw std::out_of_range("failed to create a new entity -> out of range.");
}


template<typename T, std::size_t Capacity>
inline void ObjectPool<T, Capacity>::get(const EntityId id)
{
	if (!isSlotValid(id) || !isGenValid(id.generation)) {
		return;
	}

	return entities[id];
}

template<typename T, std::size_t Capacity>
inline void ObjectPool<T, Capacity>::destroy(EntityId& id)
{
	id.slot = -1;
	id.generation = currentGeneration++;

	entities.erase(id);
	currentGeneration++;
}

template<typename T, std::size_t Capacity>
inline void ObjectPool<T, Capacity>::forEach(std::function<T>&& func)
{
	for (EntityId& entity : entities)
	{
		if (entity.slot == -1)
		{
			continue;
		}

		func();
	}
}

template<typename T, std::size_t Capacity>
inline void ObjectPool<T, Capacity>::clear()
{
	for (EntityId& entity : entities)
	{
		entity.generation = currentGeneration++;
		entity.slot = -1;
	}

	entities.clear();
	currentGeneration++;
}

template<typename T, std::size_t Capacity>
inline bool ObjectPool<T, Capacity>::isSlotValid(int id)
{
	return true ? entities[id].slot != -1 : false;
}

template<typename T, std::size_t Capacity>
inline bool ObjectPool<T, Capacity>::isGenValid(const EntityId id)
{
	return true ? id.generation == currentGeneration : false;
}
