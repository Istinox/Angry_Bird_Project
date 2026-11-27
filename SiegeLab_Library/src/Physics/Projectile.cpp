#include "Physics/Projectile.h"
#include <raylib.h>
#include <cyclone/body.h>

void Projectile::fire()
{
}

void Projectile::draw()
{
	
}

void Projectile::registerPhysics(PhysicsWorld& world)
{
	world.registerSphere(getId(), getBody(), collisionSphere);
}

void Projectile::configurePhysics()
{
}
