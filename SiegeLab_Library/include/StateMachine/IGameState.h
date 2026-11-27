#pragma once
#include "Context.h"

class IGameState
{
public:
	virtual void onEnter(Context context) = 0;
	virtual void onExit(Context context) = 0;
};
