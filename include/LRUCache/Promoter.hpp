#pragma once

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
}

namespace promoter
{
struct Promoter
{
	template<class VAL>
	static void promote(container::ListLRUContainer<VAL>& from, container::ListLRUContainer<VAL>& to)
	{
		if (from.size() == 0 || to.size() == 0)
		{
			throw std::exception("Containers empty");
		}

		auto& fromPageList = from.pageList;
		auto& toPageList = to.pageList;

		Key toKey = toPageList.front().key;
		Key fromKey = fromPageList.back().key;

		toPageList.splice(toPageList.end(), fromPageList, std::prev(fromPageList.end()));
		fromPageList.splice(fromPageList.end(), toPageList, toPageList.begin());

		from.keyToPageMap.erase(fromKey);
		from.keyToPageMap.insert(std::make_pair(toKey, std::prev(fromPageList.end())));

		to.keyToPageMap.erase(toKey);
		to.keyToPageMap.insert(std::make_pair(fromKey, std::prev(toPageList.end())));
	}

	template<class VAL, class C>
	static void promote(container::ListLRUContainer<VAL>& from, C& to)
	{
		if (from.size() == 0 || to.size() == 0)
		{
			throw std::exception("Containers empty");
		}
		
		auto toPage = to.pop();
		auto& fromPage = from.pageList.back();
		
		from.keyToPageMap.erase(fromPage.key);
		from.keyToPageMap.insert(std::make_pair(toPage.first, std::prev(from.pageList.end())));
		
		to.push(fromPage.key, std::move(fromPage.value));
		
		fromPage.key = toPage.first;
		fromPage.value = std::move(toPage.second);
	}

	template<class VAL>
	static void promote(container::VectorLRUContainer<VAL>& from, container::VectorLRUContainer<VAL>& to)
	{
		if (from.size() == 0 || to.size() == 0)
		{
			throw std::exception("Containers empty");
		}

		auto& fromPageVector = from.pageVector;
		auto& toPageVector = to.pageVector;

		Key toKey = toPageVector.front().key;
		Key fromKey = fromPageVector.back().key;

		auto latestPage = std::move(fromPageVector.back());

		fromPageVector.back() = std::move(toPageVector.front());
		std::move(std::next(toPageVector.begin()), toPageVector.end(), toPageVector.begin());
		toPageVector.back() = std::move(latestPage);

		from.keyToPageMap.erase(fromKey);
		from.keyToPageMap.insert(std::make_pair(toKey, fromPageVector.size() - 1));

		to.keyToPageMap.erase(toKey);
		to.keyToPageMap.insert(std::make_pair(fromKey, toPageVector.size() - 1));
	}

	template<class VAL, class C>
	static void promote(container::VectorLRUContainer<VAL>& from, C& to)
	{
		if (from.size() == 0 || to.size() == 0)
		{
			throw std::exception("Containers empty");
		}

		auto toPage = to.pop();
		auto fromPage = std::move(from.pageVector.back());

		from.pageVector.back().key = toPage.first;
		from.pageVector.back().value = std::move(toPage.second);

		from.keyToPageMap.erase(fromPage.key);
		from.keyToPageMap.insert(std::make_pair(toPage.first, from.pageVector.size() - 1));

		to.push(fromPage.key, std::move(fromPage.value));
	}

	template<class VAL, uint16_t N, class C>
	static void promote(container::ArrayLRUContainer<VAL, N>& from, C& to)
	{
		if (from.size() == 0 || to.size() == 0)
		{
			throw std::exception("Containers empty");
		}

		auto toPage = to.pop();
		auto& fromPage = from.pageArray[from.currentSize - 1];

		to.push(fromPage.key, std::move(fromPage.value));

		fromPage.key = toPage.first;
		fromPage.value = std::move(toPage.second);
	}
};

} // promoter
} //cache