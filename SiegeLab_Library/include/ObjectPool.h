#pragma once
#include "EntityId.h"
#include <cstddef>
#include <vector>
#include <memory>
#include <functional>
#include <stdexcept>
#include <utility>

template<typename T, std::size_t Capacity>
class ObjectPool
{
public:
	ObjectPool() : entitiesId(Capacity), entities(Capacity) {};

	EntityId create(std::unique_ptr<T> value);
	T* get(EntityId id) const;
	void destroy(EntityId id);
	void forEach(const std::function<void(T&)>& func);
	void clear();

	bool isValid(EntityId id) const;
	std::size_t getSize() const;
	bool isEmpty() const { return getSize() == 0; };

private:
	std::vector<EntityId> entitiesId;
	std::vector<std::unique_ptr<T>> entities;
};

template<typename T, std::size_t Capacity>
inline EntityId ObjectPool<T, Capacity>::create(std::unique_ptr<T> value)
{
	if (!value) throw std::invalid_argument("Failed to create a new entity -> value is nullptr.");

	for (std::size_t i = 0; i < Capacity; i++)
	{
		if (!entities[i])
		{
			entities[i] = std::move(value);
			entitiesId[i].slot = static_cast<int>(i);
			entitiesId[i].generation++;
			return entitiesId[i];
		}
	}

	throw std::out_of_range("failed to create a new entity -> pool is full.");
}

template<typename T, std::size_t Capacity>
inline T* ObjectPool<T, Capacity>::get(EntityId id) const
{
	// if (!isValid(id)) throw std::range_error("Failed to get an entity -> invalid handle.");
	return isValid(id) ? entities[id.slot].get() : nullptr;
}

template<typename T, std::size_t Capacity>
inline void ObjectPool<T, Capacity>::destroy(EntityId id)
{
	if (!isValid(id)) return;

	entities[id.slot].reset();
}

template<typename T, std::size_t Capacity>
inline void ObjectPool<T, Capacity>::forEach(const std::function<void(T&)>& func)
{
	for (auto& entity : entities)
	{
		if (entity)
			func(*entity);
	}
}

template<typename T, std::size_t Capacity>
inline void ObjectPool<T, Capacity>::clear()
{
	for (auto& entity : entities)
		entity.reset();
}

template<typename T, std::size_t Capacity>
inline bool ObjectPool<T, Capacity>::isValid(EntityId id) const
{
	return id.slot >= 0
		&& static_cast<std::size_t>(id.slot) < Capacity
		&& entities[id.slot]
		&& entitiesId[id.slot].generation == id.generation;
}

template<typename T, std::size_t Capacity>
inline std::size_t ObjectPool<T, Capacity>::getSize() const
{
	std::size_t count = 0;
	for (const auto& entity : entities)
	{
		if (entity)
			++count;
	}
	return count;
}
