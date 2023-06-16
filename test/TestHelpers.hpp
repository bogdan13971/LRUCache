#pragma once

#include <gtest/gtest.h>

#include "Entity.hpp"
#include <LRUCache/container/ILRUContainer.hpp>
#include <LRUCache/cache/LRUCache.hpp>
#include <LRUCache/cache/LayeredLRUCache.hpp>

using namespace cache;
using namespace cache::container;
using namespace cache::promoter;

using Container = ILRUContainer<Entity>;

template<CONTAINER_TYPE T>
using Cache = LRUCache<Entity, 5, T>;

template<CONTAINER_TYPE L1, CONTAINER_TYPE L2>
using LayeredCache = LayeredLRUCache<Entity, 3, 5, L1, L2>;

inline void CacheContainerSize(Container& cache)
{
	EXPECT_EQ(cache.size(), 0);

	cache.push(1, Entity(1));
	EXPECT_EQ(cache.size(), 1);

	cache.push(2, Entity(2));
	EXPECT_EQ(cache.size(), 2);
};

inline void CacheContainerContains(Container& cache)
{
	EXPECT_EQ(cache.contains(1), false);

	cache.push(1, Entity(1));
	EXPECT_EQ(cache.contains(1), true);
	EXPECT_EQ(cache.contains(2), false);

	cache.push(2, Entity(2));
	EXPECT_EQ(cache.contains(2), true);
};

inline void CacheContainerBest(Container& cache)
{
	try
	{
		Entity result = cache.best();
		FAIL();
	}
	catch (const std::exception& e)
	{
		EXPECT_EQ(e.what(), std::string("Container empty"));
	}
	catch (...)
	{
		FAIL();
	}

	Entity result;

	cache.push(1, Entity(1));
	result = cache.best();
	EXPECT_TRUE(result == Entity(1));

	cache.push(2, Entity(2));
	result = cache.best();
	EXPECT_TRUE(result == Entity(2));
};

inline void CacheContainerPush(Container& cache)
{
	cache.push(1, Entity(1));
	EXPECT_EQ(cache.size(), 1);
	EXPECT_EQ(cache.contains(1), true);

	cache.push(2, Entity(2));
	EXPECT_EQ(cache.size(), 2);
	EXPECT_EQ(cache.contains(2), true);
};

inline void CacheContainerTouch(Container& cache)
{
	try
	{
		cache.touch(4);
		FAIL();
	}
	catch (const std::exception& e)
	{
		EXPECT_EQ(e.what(), std::string("Element not in cache"));
	}
	catch (...)
	{
		FAIL();
	}

	cache.push(1, Entity(1));
	cache.push(2, Entity(2));

	cache.touch(1);

	auto result = cache.pop();
	EXPECT_EQ(result.first, 2);
	EXPECT_TRUE(result.second == Entity(2));

	result = cache.pop();
	EXPECT_EQ(result.first, 1);
	EXPECT_TRUE(result.second == Entity(1));
}

inline void CacheContainerPop(Container& cache)
{
	try
	{
		cache.pop();
		FAIL();
	}
	catch (const std::exception& e)
	{
		EXPECT_EQ(e.what(), std::string("Container empty"));
	}
	catch (...)
	{
		FAIL();
	}

	cache.push(1, Entity(1));
	cache.push(2, Entity(2));

	auto result = cache.pop();
	EXPECT_EQ(result.first, 1);
	EXPECT_TRUE(result.second == Entity(1));

	result = cache.pop();
	EXPECT_EQ(result.first, 2);
	EXPECT_TRUE(result.second == Entity(2));
}

inline void CacheContainerGetUpdate(Container& cache)
{
	EXPECT_EQ(cache.size(), 0);

	cache.push(1, Entity(1));
	cache.push(2, Entity(2));

	Entity& e = cache.best();
	e.id = 140;

	Entity e2 = cache.best();
	EXPECT_EQ(e2.id, 140);
};

template<class F, class T>
inline void Promote(F& from, T& to)
{
	from.push(1, Entity(1));
	from.push(2, Entity(2));
	from.push(3, Entity(3));
		 
	to.push(4, Entity(4));
	to.push(5, Entity(5));
	to.push(6, Entity(6));

	cache::promoter::Promoter::promote(from, to);

	EXPECT_EQ(from.contains(3), false);
	EXPECT_EQ(from.contains(4), true);
	Entity result = from.best();
	EXPECT_TRUE(result == Entity(4));

	EXPECT_EQ(to.contains(3), true);
	EXPECT_EQ(to.contains(4), false);
	result = to.best();
	EXPECT_TRUE(result == Entity(3));
}

template<CONTAINER_TYPE T>
inline void CacheLRU(Cache<T>& cache)
{
	// Add the initial 5 entities to the cache

	cache.put(1, Entity(1));
	cache.put(2, Entity(2));
	cache.put(3, Entity(3));
	cache.put(4, Entity(4));
	cache.put(5, Entity(5));

	//current cache 1-2-3-4-5

	// Generate assertions for getting the initial entities
	Entity e{};
	e = cache.get(1);
	EXPECT_TRUE(e == Entity(1));

	e = cache.get(2);
	EXPECT_TRUE(e == Entity(2));

	e = cache.get(3);
	EXPECT_TRUE(e == Entity(3));

	e = cache.get(4);
	EXPECT_TRUE(e == Entity(4));

	e = cache.get(5);
	EXPECT_TRUE(e == Entity(5));

	// Perform get and put operations to test LRU order
	cache.get(1);  // Access key 1 to make it the most recently used

	cache.put(6, Entity(6));
	cache.put(7, Entity(7));

	//cache 4-5-1-6-7

	// Assert that the entities with keys 2 and 3 have been evicted from the cache
	EXPECT_EQ(cache.contains(2), false);
	EXPECT_EQ(cache.contains(3), false);

	// Assert that the entities with keys 1, 4, 5, 6, and 7 are still in the cache
	e = cache.get(1);
	EXPECT_TRUE(e == Entity(1));

	e = cache.get(4);
	EXPECT_TRUE(e == Entity(4));

	e = cache.get(5);
	EXPECT_TRUE(e == Entity(5));

	e = cache.get(6);
	EXPECT_TRUE(e == Entity(6));

	e = cache.get(7);
	EXPECT_TRUE(e == Entity(7));

	//cache 1-4-5-6-7

	// Perform get and put operations again to test LRU order
	cache.get(4);  // Access key 4 to make it the most recently used

	cache.put(8, Entity(8));
	cache.put(9, Entity(9));

	//cache 6-7-4-8-9

	// Assert that the entities with keys 1, 5 have been evicted from the cache
	EXPECT_EQ(cache.contains(1), false);
	EXPECT_EQ(cache.contains(5), false);

	// Assert that the entities with keys 4 and 9 are still in the cache
	e = cache.get(4);
	EXPECT_TRUE(e == Entity(4));

	e = cache.get(9);
	EXPECT_TRUE(e == Entity(9));

	//cache 6-7-8-4-9
	cache.put(30, Entity(30));
	EXPECT_EQ(cache.contains(6), false);

	cache.put(31, Entity(31));
	EXPECT_EQ(cache.contains(7), false);

	cache.put(32, Entity(32));
	EXPECT_EQ(cache.contains(8), false);

	cache.put(33, Entity(33));
	EXPECT_EQ(cache.contains(4), false);

	cache.put(34, Entity(33));
	EXPECT_EQ(cache.contains(9), false);
}

template<CONTAINER_TYPE L1, CONTAINER_TYPE L2>
inline void LayeredCacheLRU(LayeredCache<L1, L2>& cache)
{
	// Add the initial 5 entities to the cache

	cache.put(1, Entity(1));
	cache.put(2, Entity(2));
	cache.put(3, Entity(3));
	cache.put(4, Entity(4));
	cache.put(5, Entity(5));
	cache.put(6, Entity(6));
	cache.put(7, Entity(7));
	cache.put(8, Entity(8));

	//current cache    6-7-8
	//               1-2-3-4-5

	// Generate assertions for getting the initial entities
	Entity e{};
	e = cache.get(1);
	EXPECT_TRUE(e == Entity(1));

	e = cache.get(2);
	EXPECT_TRUE(e == Entity(2));

	e = cache.get(3);
	EXPECT_TRUE(e == Entity(3));

	e = cache.get(4);
	EXPECT_TRUE(e == Entity(4));

	e = cache.get(5);
	EXPECT_TRUE(e == Entity(5));

	e = cache.get(6);
	EXPECT_TRUE(e == Entity(6));

	e = cache.get(7);
	EXPECT_TRUE(e == Entity(7));

	e = cache.get(8);
	EXPECT_TRUE(e == Entity(8));

	// Perform get and put operations to test LRU order
	cache.get(1);  // Access key 1 to make it the most recently used

	//   7-8-1
	// 2-3-4-5-6
	cache.put(9, Entity(9));
	cache.put(10, Entity(10));

	//   1-9-10
	// 4-5-6-7-8
		
	// Assert that the entities with keys 2 and 3 have been evicted from the cache
	EXPECT_EQ(cache.contains(2), false);
	EXPECT_EQ(cache.contains(3), false);

	// Assert that the entities with keys 1, 4, 5, 6, and 7 are still in the cache
	e = cache.get(1);
	EXPECT_TRUE(e == Entity(1));

	e = cache.get(4);
	EXPECT_TRUE(e == Entity(4));

	e = cache.get(5);
	EXPECT_TRUE(e == Entity(5));

	e = cache.get(6);
	EXPECT_TRUE(e == Entity(6));

	e = cache.get(7);
	EXPECT_TRUE(e == Entity(7));

	e = cache.get(8);
	EXPECT_TRUE(e == Entity(8));

	e = cache.get(9);
	EXPECT_TRUE(e == Entity(9));

	e = cache.get(10);
	EXPECT_TRUE(e == Entity(10));

	//  8-9-10
	// 1-4-5-6-7

	// Perform get and put operations again to test LRU order
	cache.get(4);  // Access key 4 to make it the most recently used

	//  9-10-4
	// 1-5-6-7-8

	cache.put(11, Entity(11));
	cache.put(12, Entity(12));

	//  4-11-12
	// 6-7-8-9-10

	// Assert that the entities with keys 1, 5 have been evicted from the cache
	EXPECT_EQ(cache.contains(1), false);
	EXPECT_EQ(cache.contains(5), false);

	// Assert that the entities with keys 4 and 9 are still in the cache
	e = cache.get(4);
	EXPECT_TRUE(e == Entity(4));

	e = cache.get(9);
	EXPECT_TRUE(e == Entity(9));

	//  12-4-9
	// 6-7-8-10-11

	cache.put(30, Entity(30));
	EXPECT_EQ(cache.contains(6), false);

	cache.put(31, Entity(31));
	EXPECT_EQ(cache.contains(7), false);

	cache.put(32, Entity(32));
	EXPECT_EQ(cache.contains(8), false);

	cache.put(33, Entity(33));
	EXPECT_EQ(cache.contains(10), false);

	cache.put(34, Entity(34));
	EXPECT_EQ(cache.contains(11), false);

	cache.put(35, Entity(35));
	EXPECT_EQ(cache.contains(12), false);

	cache.put(36, Entity(36));
	EXPECT_EQ(cache.contains(12), false);

	//test get update
	Entity& eref = cache.get(36);
	eref.id = 105;

	cache.put(37, Entity(37));
	EXPECT_EQ(cache.contains(4), false);

	cache.put(38, Entity(38));
	EXPECT_EQ(cache.contains(9), false);

	Entity e105 = cache.get(36);
	EXPECT_EQ(e105.id, 105);
}