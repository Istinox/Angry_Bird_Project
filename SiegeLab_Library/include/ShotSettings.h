#pragma once

#include "raylib.h"

// J'ai pas encore regarder le type de projectile.
enum class ProjectileKind
{
    TypeStandard,
    TypeHeavy
};

class ShotSettings
{
public:
    Vector3 origin{ 0.0f, 0.0f, 0.0f };
    Vector3 direction{ 1.0f, 0.0f, 0.0f };
    float speed{ 15.0f };
    ProjectileKind projectileKind{ ProjectileKind::TypeStandard };
};