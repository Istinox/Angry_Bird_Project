#pragma once
#include "../IGameState.h"

class StartState : public IGameState
{
public:
	void onEnter(Context context) override;
	void onExit(Context context) override;
};

