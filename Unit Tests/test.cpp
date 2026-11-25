#include "pch.h"
#include <gtest/gtest.h>
#include <memory>
#include <stdexcept>
#include <include/ObjectPool.h>

TEST(Pool, CapacityLimit)
{
	ObjectPool<int, 3> pool;
	const EntityId a = pool.create(std::make_unique<int>(10));
	const EntityId b = pool.create(std::make_unique<int>(20));
	const EntityId c = pool.create(std::make_unique<int>(30));

	EXPECT_THROW(pool.create(std::make_unique<int>(40)), std::out_of_range);

	ASSERT_TRUE(pool.isValid(a));
	ASSERT_TRUE(pool.isValid(b));
	ASSERT_TRUE(pool.isValid(c));
	EXPECT_EQ(*pool.get(a), 10);
	EXPECT_EQ(*pool.get(b), 20);
	EXPECT_EQ(*pool.get(c), 30);
	EXPECT_EQ(pool.getSize(), 3u);
}

TEST(Pool, RecycledSlotChangesGeneration)
{
	ObjectPool<int, 1> pool;
	const EntityId a = pool.create(std::make_unique<int>(7));
	pool.destroy(a);
	const EntityId b = pool.create(std::make_unique<int>(42));

	EXPECT_EQ(a.slot, 0);
	EXPECT_EQ(b.slot, 0);
	EXPECT_NE(b.generation, a.generation); // donc l'ID de B differe de celui de A
}

TEST(Pool, StaleHandleRejected)
{
	ObjectPool<int, 1> pool;
	const EntityId a = pool.create(std::make_unique<int>(7));
	pool.destroy(a);
	const EntityId b = pool.create(std::make_unique<int>(42));

	EXPECT_EQ(pool.get(a), nullptr);
	ASSERT_NE(pool.get(b), nullptr);
	EXPECT_EQ(*pool.get(b), 42);
}

TEST(Pool, LiveAddressStable)
{
	ObjectPool<int, 3> pool;
	const EntityId a = pool.create(std::make_unique<int>(10));
	const int* p = pool.get(a);
	ASSERT_NE(p, nullptr);

	pool.create(std::make_unique<int>(20));
	pool.create(std::make_unique<int>(30));

	EXPECT_EQ(pool.get(a), p);
	EXPECT_EQ(*pool.get(a), 10);
}

TEST(Pool, ClearInvalidatesHandles)
{
	ObjectPool<int, 2> pool;
	const EntityId a = pool.create(std::make_unique<int>(10));
	const EntityId b = pool.create(std::make_unique<int>(20));

	pool.clear();

	EXPECT_FALSE(pool.isValid(a));
	EXPECT_FALSE(pool.isValid(b));
	EXPECT_EQ(pool.getSize(), 0);

	const EntityId c = pool.create(std::make_unique<int>(30));
	ASSERT_NE(pool.get(c), nullptr);
	EXPECT_EQ(*pool.get(c), 30);

	// Les anciens ID restent invalides meme apres reutilisation d'un slot
	EXPECT_FALSE(pool.isValid(a));
	EXPECT_FALSE(pool.isValid(b));
}