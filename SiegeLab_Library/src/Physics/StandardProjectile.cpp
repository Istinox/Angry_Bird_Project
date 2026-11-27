#include "Physics/StandardProjectile.h"

void StandardProjectile::configurePhysics()
{
	float mass = 1.0f;
	float radius = 0.28f;

	cyclone::RigidBody& body = getBody();
	cyclone::CollisionSphere sphere = getCollisionSphere();

	body.setMass(mass);
	sphere.radius = radius;

	const cyclone::real coeff = 0.4f * mass * radius * radius;
	cyclone::Matrix3 inertia;
	inertia.setInertiaTensorCoeffs(coeff, coeff, coeff);
	body.setInertiaTensor(inertia);

	body.setDamping(0.99f, 0.8f); // Je savais pas quel damping mettre.
	body.setAcceleration(cyclone::Vector3(0, -9.81f, 0));
}
