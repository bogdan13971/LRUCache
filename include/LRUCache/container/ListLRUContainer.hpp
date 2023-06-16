#pragma once

#include "ILRUContainer.hpp"

#include <list>
#include <unordered_map>

namespace cache
{
namespace container
{

template <class VAL>
class ListLRUContainer : public ILRUContainer<VAL>
{
private:
	struct Page
	{
		Key key;
		VAL value;
		Page(Key key, const VAL& value): key{ key }, value{ value }
		{};
	};

	using PageList = std::list<Page>;
	using PageListIt = typename PageList::iterator;
	using KeyToPageMap = std::unordered_map<Key, PageListIt>;

private:
	KeyToPageMap keyToPageMap;
	PageList pageList;

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

		Page& page = pageList.back();

		return page.value;
	}

	const VAL& best() const override
	{
		if (size() == 0)
		{
			throw std::exception("Container empty");
		}
		
		const Page& page = pageList.back();

		return page.value;
	}

	void push(Key key, const VAL& value) override
	{
		pageList.emplace_back(key, value);

		const PageListIt latestPageIt = std::prev(pageList.end());
		keyToPageMap[key] = latestPageIt;
	}

	void push(Key key, VAL&& value) override
	{
		pageList.emplace_back(key, std::move(value));

		const PageListIt latestPageIt = std::prev(pageList.end());
		keyToPageMap[key] = latestPageIt;
	}

	void touch(Key key) override
	{
		if (!contains(key))
		{
			throw std::exception("Element not in cache");
		}

		const auto it = keyToPageMap.find(key);
		const PageListIt pageListIt = it->second;

		pageList.splice(pageList.end(), pageList, pageListIt);
		PageListIt latestPageIt = std::prev(pageList.end());

		keyToPageMap[key] = latestPageIt;
	}

	std::pair<Key, VAL> pop() override
	{
		if (size() == 0)
		{
			throw std::exception("Container empty");
		}

		Page lruPage = std::move(pageList.front());

		keyToPageMap.erase(lruPage.key);
		pageList.pop_front();

		return std::make_pair(lruPage.key, std::move(lruPage.value));
	}

	friend struct promoter::Promoter;
};

} // container
}//cache