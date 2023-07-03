#pragma once

#include <cstdint>
#include <utility>
#include <memory>

namespace cache
{
namespace container
{

using Key = uint32_t;

/**
* @brief LRU Container to be used with or without a cache
* @tparam VAL value to be stored
* @tparam N max capacity
*/
template<class VAL>
class ILRUContainer
{
	public:
	using value_type = VAL;

	public:
		ILRUContainer() = default;
		ILRUContainer(const ILRUContainer&) = delete;
		ILRUContainer& operator=(const ILRUContainer&) = delete;
		ILRUContainer(ILRUContainer&&) = default;
		ILRUContainer& operator=(ILRUContainer&&) = default;
	/**
		* @brief Get current size of the container
	*/
	virtual uint16_t size() const = 0;

	/**
		* @brief Check if key is present in the container
		* @param key Key to be searched
		* @return True if found, false otherwise
	*/
	virtual bool contains(Key key) const = 0;

	/**
		* @brief Returns the modifiable MRU element of the container
		* @throws Exception if the container is empty, use size before
		* @note Best element is the most recently used one
		* Recency is changed only by touch
	*/
	virtual VAL& best() = 0;

	/**
		* @brief Returns the MRU element of the container
		* @throws Exception if the container is empty, use size before
		* @note Best element is the most recently used one
		* Recency is changed only by touch
	*/
	virtual const VAL& best() const = 0;

	/**
		* @brief Put a key-value pair in the container
		* @note This element will become the MRU
	*/
	virtual void push(Key key, const VAL& value) = 0;

	/**
		* @brief Put a key-movable value pair in the container
		* @note This element will become the MRU
	*/
	virtual void push(Key key, VAL&& value) = 0;

	/**
		* @brief Update the recency of a key
		* @throws Exception if the key is not present, use contains before
		* @param key Key to be updated
	*/
	virtual void touch(Key key) = 0;

	/**
		* @brief Evict the LRU element of the container
		* @throws Exception if the container is empty, use size before
		* @return Returns a key-value pair of the LRU element
	*/
	virtual std::pair<Key, VAL> pop() = 0;

	virtual ~ILRUContainer() {};
};

} // container
}//cache