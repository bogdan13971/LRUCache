#pragma once

#include <cstdint>
#include "container/ContainerTypes.hpp"

namespace cache
{
namespace container
{

template<class VAL>
class ListLRUContainer;

template<class VAL>
class VectorLRUContainer;

template<class VAL, uint16_t N>
class ArrayLRUContainer;

namespace helper
{
	template<class VAL, CONTAINER_TYPE T, uint16_t N>
	struct GetContainerByType
	{
	};

	template<class VAL>
	struct GetContainerByType<VAL, CONTAINER_TYPE::ARRAY, 0>
	{
	};

	template<class VAL>
	struct GetContainerByType<VAL, CONTAINER_TYPE::LIST, 0>
	{
		using container_type = ListLRUContainer<VAL>;
	};

	template<class VAL>
	struct GetContainerByType<VAL, CONTAINER_TYPE::VECTOR, 0>
	{
		using container_type = VectorLRUContainer<VAL>;
	};

	template<class VAL, uint16_t N>
	struct GetContainerByType<VAL, CONTAINER_TYPE::ARRAY, N>
	{
		using container_type = ArrayLRUContainer<VAL, N>;
	};

	template<class VAL, CONTAINER_TYPE T, uint16_t N>
	struct GetCacheContainer
	{
		using container_type = typename GetContainerByType<VAL, T, 0>::container_type;
	};

	template<class VAL, uint16_t N>
	struct GetCacheContainer<VAL, CONTAINER_TYPE::ARRAY, N>
	{
		using container_type = typename GetContainerByType<VAL, CONTAINER_TYPE::ARRAY, N>::container_type;
	};

} // helper
} // container
} // cache