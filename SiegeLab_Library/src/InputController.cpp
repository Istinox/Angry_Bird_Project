#include "InputController.h"

#include "raylib.h"

float InputController::readAxis(int negativeKey, int positiveKey)
{
	float axisValue = 0.0f;
	if (IsKeyDown(negativeKey)) axisValue -= 1.f;
	if (IsKeyDown(positiveKey)) axisValue += 1.f;

	return axisValue;
}

void InputController::capture()
{
	inputLauncher.yawAxis = readAxis(KEY_A, KEY_D);
	inputLauncher.pitchAxis = readAxis(KEY_S, KEY_W);
	inputLauncher.speedAxis = readAxis(KEY_Q, KEY_E);
	inputLauncher.selectTypeStandard = IsKeyPressed(KEY_ONE);
	inputLauncher.selectTypeHeavy = IsKeyPressed(KEY_TWO);
}
