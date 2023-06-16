#include "TestHelpers.hpp"
#include <LRUCache/CacheHelper.hpp>

using namespace cache;
using namespace cache::container;


TEST(LayeredLRU, VectorListLayers)
{
	LayeredCache<CONTAINER_TYPE::VECTOR, CONTAINER_TYPE::LIST> cache;
	LayeredCacheLRU(cache);
}

TEST(LayeredLRU, VectorVectorLayers)
{
	LayeredCache<CONTAINER_TYPE::VECTOR, CONTAINER_TYPE::VECTOR> cache;
	LayeredCacheLRU(cache);
}

TEST(LayeredLRU, VectorArrayLayers)
{
	LayeredCache<CONTAINER_TYPE::VECTOR, CONTAINER_TYPE::ARRAY> cache;
	LayeredCacheLRU(cache);
}

TEST(LayeredLRU, ListListLayers)
{
	LayeredCache<CONTAINER_TYPE::LIST, CONTAINER_TYPE::LIST> cache;
	LayeredCacheLRU(cache);
}

TEST(LayeredLRU, ListVectorLayers)
{
	LayeredCache<CONTAINER_TYPE::LIST, CONTAINER_TYPE::VECTOR> cache;
	LayeredCacheLRU(cache);
}

TEST(LayeredLRU, ListArrayLayers)
{
	LayeredCache<CONTAINER_TYPE::LIST, CONTAINER_TYPE::ARRAY> cache;
	LayeredCacheLRU(cache);
}

TEST(LayeredLRU, ArrayListLayers)
{
	LayeredCache<CONTAINER_TYPE::ARRAY, CONTAINER_TYPE::LIST> cache;
	LayeredCacheLRU(cache);
}

TEST(LayeredLRU, ArrayVectorLayers)
{
	LayeredCache<CONTAINER_TYPE::ARRAY, CONTAINER_TYPE::VECTOR> cache;
	LayeredCacheLRU(cache);
}

TEST(LayeredLRU, ArrayArrayLayers)
{
	LayeredCache<CONTAINER_TYPE::ARRAY, CONTAINER_TYPE::ARRAY> cache;
	LayeredCacheLRU(cache);
}