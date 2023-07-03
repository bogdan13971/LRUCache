#pragma once

#include "ILRUContainer.hpp"

#include <array>

namespace cache
{
namespace container
{

template <class VAL, uint16_t N>
class ArrayLRUContainer : public ILRUContainer<VAL>
{
private:
	struct Page
	{
		Key key;
		VAL value;
		Page() :key{ 0 }, value{} {};
		Page(Key key, const VAL& value) :key{ key }, value{ value }{};
	};

	using PageArray = std::array<Page, N>;

private:
	PageArray pageArray;
	uint16_t currentSize = 0;

	size_t find(Key key) const
	{
		for (size_t i = 0; i < currentSize; i++)
		{
			const Page& page = pageArray[i];
			if (page.key == key)
			{
				return i;
			}
		}

		return -1;
	}

public:
	uint16_t size() const override
	{
		return currentSize;
	}

	bool contains(Key key) const override
	{
		return find(key) != -1;
	}

	VAL& best() override
	{
		if (size() == 0)
		{
			throw std::exception("Container empty");
		}

		Page& page = pageArray[currentSize - 1];

		return page.value;
	}

	const VAL& best() const override
	{
		if (size() == 0)
		{
			throw std::exception("Container empty");
		}

		const Page& page = pageArray[currentSize - 1];

		return page.value;
	}

	void push(Key key, const VAL& value) override
	{
		if (size() == N)
		{
			throw std::exception("Container full");
		}

		Page page(key, value);
		pageArray[currentSize] = std::move(page);

		currentSize++;
	}

	void push(Key key, VAL&& value) override
	{
		if (size() == N)
		{
			throw std::exception("Container full");
		}

		Page page(key, std::move(value));
		pageArray[currentSize] = std::move(page);

		currentSize++;
	}

	void touch(Key key) override
	{
		size_t index = find(key);
		if (index == -1)
		{
			throw std::exception("Element not in cache");
		}

		if (pageArray[currentSize - 1].key == key)
		{
			return;
		}

		Page latestPage = std::move(pageArray[index]);
		std::move(pageArray.begin() + index + 1, pageArray.begin() + currentSize, pageArray.begin() + index);
		pageArray[currentSize - 1] = std::move(latestPage);
	}

	std::pair<Key, VAL> pop() override
	{
		if (size() == 0)
		{
			throw std::exception("Container empty");
		}

		Page lruPage = std::move(pageArray.front());

		std::move(std::next(pageArray.begin()), pageArray.end(), pageArray.begin());

		currentSize--;

		return std::make_pair(lruPage.key, std::move(lruPage.value));
	}

	friend struct Promoter;
};

} // container
}//cache