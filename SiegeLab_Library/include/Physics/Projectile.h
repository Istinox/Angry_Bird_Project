#pragma once
#include "GameEntity.h"
#include <cyclone/collide_fine.h>

class Projectile : public GameEntity
{
private:
	cyclone::CollisionSphere collisionSphere;

	//struct HeavyProjectile {
	//	float mass = 2.0f;
	//	float radius = 0.36f;
	//	void configurePhysics();
	//};

public:
	Projectile(EntityId id) : GameEntity(id) { collisionSphere.body = &getBody(); };
	void fire(); // ShotSettings.
	void draw() override;
	void registerPhysics(PhysicsWorld& world) override;
	virtual void configurePhysics() = 0;
};

