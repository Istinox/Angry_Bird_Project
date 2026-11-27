#include "Launcher.h"
#include "raymath.h"

Launcher::Launcher(Vector3 origin_) : origin(origin_)
{
}

void Launcher::aim(const InputController::InputLauncher& input)
{
    yaw   = Clamp(yaw + input.yawAxis, MIN_YAW, MAX_YAW);
    pitch = Clamp(pitch + input.pitchAxis, MIN_PITCH, MAX_PITCH);
    speed = Clamp(speed + input.speedAxis, MIN_SPEED, MAX_SPEED);

    if (input.selectTypeStandard) {
        projectileKind = ProjectileKind::TypeStandard;
    }
    if (input.selectTypeHeavy) {
        projectileKind = ProjectileKind::TypeHeavy;
    }
}

ShotSettings Launcher::shotSettings() const
{
    Vector3 direction{ 1.0f, 0.0f, 0.0f };
    direction = Vector3Transform(direction, MatrixRotateZ(pitch * DEG2RAD));
    direction = Vector3Transform(direction, MatrixRotateY(-yaw * DEG2RAD));

    ShotSettings settings
    {
        .origin = origin,
        .direction = Vector3Normalize(direction),
        .speed = speed,
        .projectileKind = projectileKind
    };

    return settings;
}
