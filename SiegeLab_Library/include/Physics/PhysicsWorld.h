#pragma once
#include "EntityId.h"
#include <cyclone/body.h>
#include <cyclone/collide_fine.h> // cyclone::CollisionSphere
#include "PhysicsRegistration.h"
#include <vector>
#include <SceneObjects.h>

using namespace cyclone;

template<typename std::size_t MaxEntities>
class PhysicsWorld
{
public:
	void registerSphere(EntityId id, RigidBody& body, CollisionSphere& sphere);
	void registerBox(EntityId id, RigidBody& body, CollisionBox& box);
	void registerPlane(CollisionPlane& plane);
	void step(double deltaTime);
	void unregisterObject(EntityId id);
private:
	std::vector<PhysicsRegistration> physicsRegistrations;
	// template<std::size_t MaxEntities>
	// SceneObjects<MaxEntities>* sceneObject = nullptr;
};

template<std::size_t MaxEntities>
inline void PhysicsWorld<MaxEntities>::registerSphere(EntityId id, RigidBody& body, CollisionSphere& sphere)
{
}

template<std::size_t MaxEntities>
inline void PhysicsWorld<MaxEntities>::registerBox(EntityId id, RigidBody& body, CollisionBox& box)
{
}

template<std::size_t MaxEntities>
inline void PhysicsWorld<MaxEntities>::registerPlane(CollisionPlane& plane)
{
}

template<std::size_t MaxEntities>
inline void PhysicsWorld<MaxEntities>::step(double deltaTime)
{
}

template<std::size_t MaxEntities>
inline void PhysicsWorld<MaxEntities>::unregisterObject(EntityId id)
{
}
