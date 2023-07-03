#pragma once

#include "LRUCache/helpers/ContainerTypeHelper.hpp"
#include "LRUCache/Promoter.hpp"

#include <utility>

namespace cache
{
/**
	* @brief Cache with LRU eviction policy distributed on 2 layers
	* @tparam VAL Value type to be stored
	* @tparam P Promoter used to promote a value from the second layer to the first
	* @tparam N1 Size of first layer
	* @tparam N2 Size of second layer
	* @tparam T1 Type of first layer container
	* @tparam T2 Type of second layer container
*/
template<class VAL, uint16_t N1, uint16_t N2,
	container::CONTAINER_TYPE T1 = container::CONTAINER_TYPE::VECTOR, 
	container::CONTAINER_TYPE T2 = container::CONTAINER_TYPE::LIST,
	class P = promoter::Promoter>
class LayeredLRUCache
{
public:
	using value_type = VAL;

private:
	using C1 = typename container::helper::GetCacheContainer<VAL, T1, N1>::container_type;
	using C2 = typename container::helper::GetCacheContainer<VAL, T2, N2>::container_type;

	C1 firstLayer;
	C2 secondLayer;
	P promoter;

public:
	bool contains(container::Key key) const
	{
		return firstLayer.contains(key)
			|| secondLayer.contains(key);
	}

	VAL& get(container::Key key)
	{
		if (firstLayer.contains(key))
		{
			firstLayer.touch(key);
		}
		else
		{
			secondLayer.touch(key);
			promoter.promote(secondLayer, firstLayer);
		}

		return firstLayer.best();
	}

	const VAL& get(container::Key key) const
	{
		if (firstLayer.contains(key))
		{
			firstLayer.touch(key);
		}
		else
		{
			secondLayer.touch(key);
			promoter.promote(secondLayer, firstLayer);
		}

		return firstLayer.best();
	}

	void put(container::Key key, const VAL& val)
	{
		if (firstLayer.contains(key) || secondLayer.contains(key))
		{
			return;
		}

		if (firstLayer.size() == N1)
		{
			auto page = firstLayer.pop();
			if (secondLayer.size() == N2)
			{
				secondLayer.pop();
			}
			secondLayer.push(page.first, std::move(page.second));
		}

		firstLayer.push(key, val);
	}

	void put(container::Key key, VAL&& val)
	{
		if (firstLayer.contains(key) || secondLayer.contains(key))
		{
			return;
		}

		if (firstLayer.size() == N1)
		{
			auto page = firstLayer.pop();
			if (secondLayer.size() == N2)
			{
				secondLayer.pop();
			}
			secondLayer.push(page.first, std::move(page.second));
		}

		firstLayer.push(key, std::move(val));
	}

	friend struct promoter::Promoter;
};

} // cache