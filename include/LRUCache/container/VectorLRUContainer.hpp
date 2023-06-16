#pragma once

#include "ILRUContainer.hpp"

#include <vector>
#include <unordered_map>

namespace cache
{
namespace container
{

template <class VAL>
class VectorLRUContainer : public ILRUContainer<VAL>
{
private:
	struct Page
	{
		Key key;
		VAL value;
		Page(Key key, const VAL& value) :key{ key }, value{ value }{};
	};

	using PageVector = std::vector<Page>;
	using KeyToPageMap = std::unordered_map<Key, size_t>;

private:
	KeyToPageMap keyToPageMap;
	PageVector pageVector;

private:
	void update(size_t start)
	{
		for (size_t i = start; i < pageVector.size() - 1; i++)
		{
			Page& page = pageVector[i];
			page = std::move(pageVector[i + 1]);
			keyToPageMap[page.key] = i;
		}
	}

public:
	uint16_t size() const override
	{
		return static_cast<uint16_t>(keyToPageMap.size());
	}

	bool contains(Key key) const override
	{
		if (size() == 0)
		{
			return false;
		}

		return keyToPageMap.find(key) != keyToPageMap.end();
	}

	VAL& best() override
	{
		if (size() == 0)
		{
			throw std::exception("Container empty");
		}

		Page& page = pageVector.back();

		return page.value;
	}

	const VAL& best() const override
	{
		if (size() == 0)
		{
			throw std::exception("Container empty");
		}

		const Page& page = pageVector.back();

		return page.value;
	}

	void push(Key key, const VAL& value) override
	{
		pageVector.emplace_back(key, value);

		keyToPageMap[key] = pageVector.size() - 1;
	}

	void push(Key key, VAL&& value) override
	{
		pageVector.emplace_back(key, std::move(value));

		keyToPageMap[key] = pageVector.size() - 1;
	}

	void touch(Key key) override
	{
		if (!contains(key))
		{
			throw std::exception("Element not in cache");
		}

		const auto it = keyToPageMap.find(key);
		const size_t index = it->second;

		Page latestPage = std::move(pageVector[index]);

		update(index);

		pageVector.back() = std::move(latestPage);
		keyToPageMap[key] = pageVector.size() - 1;
	}

	std::pair<Key, VAL> pop() override
	{
		if (size() == 0)
		{
			throw std::exception("Container empty");
		}

		Page lruPage = std::move(pageVector.front());

		update(0);
		pageVector.pop_back();
		keyToPageMap.erase(lruPage.key);

		return std::make_pair(lruPage.key, std::move(lruPage.value));
	}

	friend struct promoter::Promoter;
};

} // container
}//cache