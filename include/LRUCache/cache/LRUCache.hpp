#pragma once

#include "helpers/ContainerTypeHelper.hpp"

namespace cache
{
/**
 * @brief Cache with LRU eviction policy
 * @tparam VAL Value type to be stored
 * @tparam N Size of cache
 * @tparam T Type of underlying container
*/
template<class VAL, uint16_t N, 
	container::CONTAINER_TYPE T = container::CONTAINER_TYPE::LIST>
class LRUCache
{
private:
	using C = typename container::helper::GetCacheContainer<VAL, T, N>::container_type;

	C container;

public:
	bool contains(container::Key key) const
	{
		return container.contains(key);
	}

	VAL& get(container::Key key)
	{
		container.touch(key);

		return container.best();
	}

	const VAL& get(container::Key key) const
	{
		container.touch(key);

		return container.best();
	}

	void put(container::Key key, const VAL& value)
	{
		if (container.contains(key))
		{
			return;
		}

		if (container.size() == N)
		{
			container.pop();
		}

		container.push(key, value);
	}

	void put(container::Key key, VAL&& value)
	{
		if (container.contains(key))
		{
			return;
		}

		if (container.size() == N)
		{
			container.pop();
		}

		container.push(key, std::move(value));
	}
};

} // cache