#pragma once
#include "EntityId.h"
#include <cstddef>
#include <vector>
#include <functional>
#include <utility>

template<typename T, std::size_t Capacity>
class ObjectPool
{
public:
	ObjectPool() : entitiesId(Capacity), entities(Capacity, nullptr) {};
	~ObjectPool() { clear(); }

	template<typename U = T, typename... Args> // U = T c'est simplement pour ajouter une valeur par défaut.
	EntityId create(Args&&... args);

	T* get(EntityId id) const;
	void destroy(EntityId id);
	void forEach(const std::function<void(T&)>& func);
	void clear();

	bool isValid(EntityId id) const;
	std::size_t getSize() const;
	bool isEmpty() const { return getSize() == 0; };

private:
	std::vector<EntityId> entitiesId;
	std::vector<T*> entities;
};

template<typename T, std::size_t Capacity>
template<typename U, typename... Args>
inline EntityId ObjectPool<T, Capacity>::create(Args&&... args)
{
	for (std::size_t i = 0; i < Capacity; i++)
	{
		if (entities[i]) continue;

		entities[i] = new U(std::forward<Args>(args)...);
		entitiesId[i].slot = static_cast<int>(i);
		entitiesId[i].generation++;
		return entitiesId[i];
	}

	return EntityId{ -1, 0 };
}

template<typename T, std::size_t Capacity>
inline T* ObjectPool<T, Capacity>::get(EntityId id) const
{
	// if (!isValid(id)) throw std::range_error("Failed to get an entity -> invalid handle.");
	return isValid(id) ? entities[id.slot] : nullptr;
}

template<typename T, std::size_t Capacity>
inline void ObjectPool<T, Capacity>::destroy(EntityId id)
{
	if (!isValid(id)) return;

	delete entities[id.slot];
	entities[id.slot] = nullptr;
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
	for (T*& entity : entities)
	{
		delete entity;
		entity = nullptr;
	}
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
	for (const T* entity : entities)
	{
		if (entity)
			++count;
	}
	return count;
}
