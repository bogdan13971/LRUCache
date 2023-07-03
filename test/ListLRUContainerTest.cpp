#include "TestHelpers.hpp"
#include "LRUCache/CacheHelper.hpp"

using namespace cache;
using namespace cache::container;

TEST(ListLRUContainer, Size)
{
	ListLRUContainer<Entity> listContainer;
	CacheContainerSize(listContainer);
}

TEST(ListLRUContainer, Contains)
{
	ListLRUContainer<Entity> listContainer;
	CacheContainerContains(listContainer);
}

TEST(ListLRUContainer, Best)
{
	ListLRUContainer<Entity> listContainer;
	CacheContainerBest(listContainer);
}

TEST(ListLRUContainer, Push)
{
	ListLRUContainer<Entity> listContainer;
	CacheContainerPush(listContainer);
}

TEST(ListLRUContainer, Touch)
{
	ListLRUContainer<Entity> listContainer;
	CacheContainerTouch(listContainer);
}

TEST(ListLRUContainer, Pop)
{
	ListLRUContainer<Entity> listContainer;
	CacheContainerPop(listContainer);
}

TEST(ListLRUContainer, GetUpdate)
{
	ListLRUContainer<Entity> listContainer;
	CacheContainerGetUpdate(listContainer);
}

TEST(LRUCache, ListContainer)
{
	Cache<CONTAINER_TYPE::LIST> cache;
	CacheLRU(cache);
}

TEST(LRUPromoter, ListToList)
{
	ListLRUContainer<Entity> from;
	ListLRUContainer<Entity> to;

	Promote(from, to);
}

TEST(LRUPromoter, ListToVector)
{
	ListLRUContainer<Entity> from;
	VectorLRUContainer<Entity> to;

	Promote(from, to);
}

TEST(LRUPromoter, ListToArray)
{
	ListLRUContainer<Entity> from;
	ArrayLRUContainer<Entity, 6> to;

	Promote(from, to);
}