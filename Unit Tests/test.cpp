#include "pch.h"
#include <include/Game.h>
#include <include/ObjectPool.h>

TEST(TestCaseName, PoolCapacityLimit) {

	Game game;
	ObjectPool<int, 40> objectPool;

  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}