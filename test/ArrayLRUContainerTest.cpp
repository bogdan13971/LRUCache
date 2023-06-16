#include "TestHelpers.hpp"
#include <LRUCache/CacheHelper.hpp>

using namespace cache;
using namespace cache::container;

TEST(ArrayLRUContainer, Size)
{
	ArrayLRUContainer<Entity, 5> arrayContainer;
	CacheContainerSize(arrayContainer);
}

TEST(ArrayLRUContainer, Contains)
{
	ArrayLRUContainer<Entity, 5> arrayContainer;
	CacheContainerContains(arrayContainer);
}

TEST(ArrayLRUContainer, Best)
{
	ArrayLRUContainer<Entity, 5> arrayContainer;
	CacheContainerBest(arrayContainer);
}

TEST(ArrayLRUContainer, Push)
{
	ArrayLRUContainer<Entity, 5> arrayContainer;
	CacheContainerPush(arrayContainer);
}

TEST(ArrayLRUContainer, Touch)
{
	ArrayLRUContainer<Entity, 5> arrayContainer;
	CacheContainerTouch(arrayContainer);
}

TEST(ArrayLRUContainer, Pop)
{
	ArrayLRUContainer<Entity, 5> arrayContainer;
	CacheContainerPop(arrayContainer);
}

TEST(ArrayLRUContainer, GetUpdate)
{
	ArrayLRUContainer<Entity, 5> arrayContainer;
	CacheContainerGetUpdate(arrayContainer);
}

TEST(LRUCache, ArrayContainer)
{
	Cache<CONTAINER_TYPE::ARRAY> cache;
	CacheLRU(cache);
}

TEST(LRUPromoter, ArrayToArray)
{
	ArrayLRUContainer<Entity, 5> from;
	ArrayLRUContainer<Entity, 5> to;

	Promote(from, to);
}

TEST(LRUPromoter, ArrayToVector)
{
	ArrayLRUContainer<Entity, 5> from;
	VectorLRUContainer<Entity> to;

	Promote(from, to);
}

TEST(LRUPromoter, ArrayToList)
{
	ArrayLRUContainer<Entity, 5> from;
	ListLRUContainer<Entity> to;

	Promote(from, to);
}