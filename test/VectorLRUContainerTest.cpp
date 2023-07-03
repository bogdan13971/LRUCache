#include "TestHelpers.hpp"
#include "LRUCache/CacheHelper.hpp"

using namespace cache;
using namespace cache::container;

TEST(VectorLRUContainer, Size)
{
	VectorLRUContainer<Entity> vectorContainer;
	CacheContainerSize(vectorContainer);
}

TEST(VectorLRUContainer, Contains)
{
	VectorLRUContainer<Entity> vectorContainer;
	CacheContainerContains(vectorContainer);
}

TEST(VectorLRUContainer, Best)
{
	VectorLRUContainer<Entity> vectorContainer;
	CacheContainerBest(vectorContainer);
}

TEST(VectorLRUContainer, Push)
{
	VectorLRUContainer<Entity> vectorContainer;
	CacheContainerPush(vectorContainer);
}

TEST(VectorLRUContainer, Touch)
{
	VectorLRUContainer<Entity> vectorContainer;
	CacheContainerTouch(vectorContainer);
}

TEST(VectorLRUContainer, Pop)
{
	VectorLRUContainer<Entity> vectorContainer;
	CacheContainerPop(vectorContainer);
}

TEST(VectorLRUContainer, GetUpdate)
{
	VectorLRUContainer<Entity> vectorContainer;
	CacheContainerGetUpdate(vectorContainer);
}

TEST(LRUCache, VectorContainer)
{
	Cache<CONTAINER_TYPE::VECTOR> cache;
	CacheLRU(cache);
}

TEST(LRUPromoter, VectorToVector)
{
	VectorLRUContainer<Entity> from;
	VectorLRUContainer<Entity> to;

	Promote(from, to);
}

TEST(LRUPromoter, VectorToList)
{
	VectorLRUContainer<Entity> from;
	ListLRUContainer<Entity> to;

	Promote(from, to);
}

TEST(LRUPromoter, VectorToArray)
{
	VectorLRUContainer<Entity> from;
	ArrayLRUContainer<Entity, 6> to;

	Promote(from, to);
}