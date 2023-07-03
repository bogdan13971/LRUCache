#pragma once

#include "LRUCache/container/ArrayLRUContainer.hpp"
#include "LRUCache/container/ListLRUContainer.hpp"
#include "LRUCache/container/VectorLRUContainer.hpp"

#include "LRUCache/helpers/ContainerTypeHelper.hpp"

#include "LRUCache/cache/LRUCache.hpp"
#include "LRUCache/cache/LayeredLRUCache.hpp"

namespace cache
{
namespace container
{
/**
	* @brief Create a container based on a type
	* @tparam VAL Value for the items in the container
	* @tparam T Container type
	* @tparam N Container size. Only for fixed size containers
*/
template<class VAL, CONTAINER_TYPE T = CONTAINER_TYPE::LIST, uint16_t N = 0>
typename helper::GetContainerByType<VAL, T, N>::container_type CreateContainer()
{
	return helper::GetContainerByType<VAL, T, N>::container_type();
};

} // containers

/**
 * @brief Create a cache based on a type and a size
 * @tparam VAL Value type to be stored
 * @tparam N Size of cache
 * @tparam T Type of cache
*/
template<class VAL, uint16_t N, container::CONTAINER_TYPE T = container::CONTAINER_TYPE::LIST>
LRUCache<VAL, N, T> CreateCache()
{
	return LRUCache<VAL, N, T>();
}

/**
	* @brief Create a 2 layered cache with LRU eviction policy
	* @tparam VAL Value type to be stored
	* @tparam P Promoter used to promote a value from the second layer to the first
	* @tparam N1 Size of first layer
	* @tparam N2 Size of second layer
	* @tparam T1 Type of first layer container
	* @tparam T2 Type of second layer container
*/
template<class VAL, uint16_t N1, uint16_t N2,
	container::CONTAINER_TYPE T1 = container::CONTAINER_TYPE::ARRAY,
	container::CONTAINER_TYPE T2 = container::CONTAINER_TYPE::LIST,
	class P = promoter::Promoter>
LayeredLRUCache<VAL, N1, N2, T1, T2, P> CreateLayeredCache()
{
	return LayeredLRUCache<VAL, N1, N2, T1, T2, P>();
}

} // cache