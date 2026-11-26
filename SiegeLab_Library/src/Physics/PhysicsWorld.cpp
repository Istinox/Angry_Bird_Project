#include "Physics/PhysicsWorld.h"

void PhysicsWorld::registerSphere(EntityId id, cyclone::RigidBody& body, cyclone::CollisionSphere& sphere)
{
	PhysicsRegistration physicRegistrationSphere
	{
		.id = id,
		.bodyPtr = &body,
		.collisionPtr = &sphere
	};

	physicsRegistrations.push_back(physicRegistrationSphere);
}

void PhysicsWorld::registerBox(EntityId id, cyclone::RigidBody& body, cyclone::CollisionBox& box)
{
	PhysicsRegistration physicRegistrationBox
	{
		.id = id,
		.bodyPtr = &body,
		.collisionPtr = &box
	};

	physicsRegistrations.push_back(physicRegistrationBox);
}

void PhysicsWorld::registerPlane(cyclone::CollisionPlane& plane)
{
	collisionPlanes.push_back(plane);
}

void PhysicsWorld::step(double deltaTime)
{
	for (PhysicsRegistration& physics : physicsRegistrations)
	{
		if (!isRigidBodyValid(physics.bodyPtr)) {
			continue;
		}

		// cycloneContactResolvers (??)
	}
}

void PhysicsWorld::unregisterObject(EntityId id)
{
	physicsRegistrations[id.slot] = { };
}

bool PhysicsWorld::isRigidBodyValid(cyclone::RigidBody* rigidBody) const
{
	return rigidBody && rigidBody->hasFiniteMass();
}