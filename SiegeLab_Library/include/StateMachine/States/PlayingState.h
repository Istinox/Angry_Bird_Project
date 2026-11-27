#pragma once
#include "../IGameState.h"

class PlayingState : public IGameState
{
	void onEnter(Context context) override;
	void onExit(Context context) override;
};

