#pragma once
#include <raylib.h>
#include "ShotSettings.h"
#include "InputController.h"

class Launcher
{
public:
	Launcher(Vector3 origin_);

	void aim(const InputController::InputLauncher& input);
	ShotSettings shotSettings() const;

private:
	Vector3 origin;
	float yaw	= 0.0f; // azimuth
	float pitch = 0.0f; // elevation
	float speed = 0.0f;
	ProjectileKind projectileKind{ ProjectileKind::TypeStandard };

	const float MIN_YAW   = -30.f;
	const float MAX_YAW   = 30.f;
	const float MIN_PITCH = 5.f;
	const float MAX_PITCH = 55.f;
	const float MIN_SPEED = 8.f;
	const float MAX_SPEED = 22.f;
};

