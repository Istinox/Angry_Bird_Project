#pragma once
#include "Physics/PhysicsWorld.h"

class GameEntity
{
public:
	GameEntity(EntityId id) : id(id) {}
	virtual ~GameEntity() = default;
	virtual void draw() {};
	virtual void registerPhysics(PhysicsWorld& world);

	EntityId getId() const { return id; }
	cyclone::RigidBody& getBody() { return body; }

private:
	EntityId id;
	cyclone::RigidBody body;
};

