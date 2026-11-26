#pragma once
#include "EntityId.h"
#include <cyclone/body.h>
#include <cyclone/collide_fine.h> // cyclone::CollisionPrimitive

using namespace cyclone;

struct PhysicsRegistration
{
public:
	EntityId id								  = {};
	cyclone::RigidBody* bodyPtr				  = nullptr;
	cyclone::CollisionPrimitive* collisionPtr = nullptr;
};

