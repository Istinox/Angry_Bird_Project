#include "pch.h"

#include <gtest/gtest.h>

#include <include/ObjectPool.h>
#include <include/SceneObjects.h>
#include <include/Physics/PhysicsWorld.h>

// P01 - P05
TEST(Pool, CapacityLimit)
{
	ObjectPool<int, 3> pool;
	const EntityId a = pool.create(10);
	const EntityId b = pool.create(20);
	const EntityId c = pool.create(30);

	const EntityId overflow = pool.create(40);
	EXPECT_FALSE(pool.isValid(overflow));
	EXPECT_EQ(pool.get(overflow), nullptr);

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
	const EntityId a = pool.create(7);
	pool.destroy(a);
	const EntityId b = pool.create(42);

	EXPECT_EQ(a.slot, 0);
	EXPECT_EQ(b.slot, 0);
	EXPECT_NE(b.generation, a.generation); // donc l'ID de B differe de celui de A
}

TEST(Pool, StaleHandleRejected)
{
	ObjectPool<int, 1> pool;
	const EntityId a = pool.create(7);
	pool.destroy(a);
	const EntityId b = pool.create(42);

	EXPECT_EQ(pool.get(a), nullptr);
	ASSERT_NE(pool.get(b), nullptr);
	EXPECT_EQ(*pool.get(b), 42);
}

TEST(Pool, LiveAddressStable)
{
	ObjectPool<int, 3> pool;
	const EntityId a = pool.create(10);
	const int* p = pool.get(a);
	ASSERT_NE(p, nullptr);

	pool.create(20);
	pool.create(30);

	EXPECT_EQ(pool.get(a), p);
	EXPECT_EQ(*pool.get(a), 10);
}

TEST(Pool, ClearInvalidatesHandles)
{
	ObjectPool<int, 2> pool;
	const EntityId a = pool.create(10);
	const EntityId b = pool.create(20);

	pool.clear();

	EXPECT_FALSE(pool.isValid(a));
	EXPECT_FALSE(pool.isValid(b));
	EXPECT_EQ(pool.getSize(), 0u);

	const EntityId c = pool.create(30);
	const EntityId d = pool.create(40);
	ASSERT_NE(pool.get(c), nullptr);
	ASSERT_NE(pool.get(d), nullptr);
	EXPECT_EQ(*pool.get(c), 30);
	EXPECT_EQ(*pool.get(d), 40);

	// Les anciens ID restent invalides meme apres reutilisation des slots
	EXPECT_FALSE(pool.isValid(a));
	EXPECT_FALSE(pool.isValid(b));
}

// GO01 (Presque fait), GO05, GO06 (Pas fait)

TEST(sceneObjects, EntitiesFactoryCreatesDerivedTypes)
{
	class StandardProjectile : public GameEntity {};
	class HeavyProjectile : public GameEntity {};

	SceneObjects<4> scene;
	const EntityId a = scene.createEntity<StandardProjectile>();
	const EntityId b = scene.createEntity<HeavyProjectile>();

	GameEntity* first = scene.get(a);
	GameEntity* second = scene.get(b);

	ASSERT_NE(first, nullptr);
	ASSERT_NE(second, nullptr);
}