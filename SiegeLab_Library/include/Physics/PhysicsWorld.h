#pragma once
#include "../EntityId.h"

#include <vector>

#include <cyclone/body.h>
#include <cyclone/collide_fine.h> // cyclone::CollisionSphere
#include <cyclone/contacts.h>

#include "PhysicsRegistration.h"

class PhysicsWorld
{
public:
	void registerSphere(EntityId id, cyclone::RigidBody& body, cyclone::CollisionSphere& sphere);
	void registerBox(EntityId id, cyclone::RigidBody& body, cyclone::CollisionBox& box);
	void registerPlane(cyclone::CollisionPlane& plane);
	void step(double deltaTime);
	void unregisterObject(EntityId id);

	// Vérifie si la masse inversé est strictement positif / existante.
	bool isRigidBodyValid(RigidBody* rigidBody) const;

private:
	std::vector<PhysicsRegistration> physicsRegistrations = {};
	std::vector<cyclone::CollisionPlane*> collisionPlanes = {};
};
