#pragma once
#include <raylib.h>

class InputController
{
public:
    struct InputLauncher {
        float yawAxis = 0.0f;
        float pitchAxis = 0.0f;
        float speedAxis = 0.0f;
        bool selectTypeStandard = false;
        bool selectTypeHeavy = false;
    };

	float readAxis(int negativeKey, int positiveKey);
	void capture();

    InputLauncher inputLauncher;
};

