#include <LRUCache/CacheHelper.hpp>

int main()
{
	using namespace cache;
	using namespace cache::container;

	ListLRUContainer<int> listCont;
	VectorLRUContainer<int> vecCont;
	ArrayLRUContainer<int, 3> arrCont;

	auto listCont1 = CreateContainer<int>();
	auto listCont2 = CreateContainer<int, CONTAINER_TYPE::LIST>();
	auto vecCont1 = CreateContainer<int, CONTAINER_TYPE::VECTOR>();
	auto arrCont2 = CreateContainer<int, CONTAINER_TYPE::ARRAY, 10>();

	LRUCache<int, 10> listCache;
	LRUCache<int, 10, CONTAINER_TYPE::LIST> listCache1;
	LRUCache<int, 10, CONTAINER_TYPE::VECTOR> vecCache;
	LRUCache<int, 10, CONTAINER_TYPE::ARRAY> arrCache;

	auto listCache2 = CreateCache<int, 10>;
	auto listCache3 = CreateCache<int, 10, CONTAINER_TYPE::LIST>;
	auto vecCache1 = CreateCache<int, 10, CONTAINER_TYPE::VECTOR>;
	auto arrCache1 = CreateCache<int, 10, CONTAINER_TYPE::ARRAY>;

	LayeredLRUCache<int, 4, 5> defaultLayered;
	LayeredLRUCache<int, 4, 5, CONTAINER_TYPE::LIST, CONTAINER_TYPE::VECTOR> layered1;
	LayeredLRUCache<int, 4, 5, CONTAINER_TYPE::LIST, CONTAINER_TYPE::ARRAY> layered2;
	LayeredLRUCache<int, 4, 5, CONTAINER_TYPE::ARRAY, CONTAINER_TYPE::ARRAY> layered3;

	auto layered4 = CreateLayeredCache<int, 4, 5>();
	auto layered5 = CreateLayeredCache<int, 4, 5, CONTAINER_TYPE::LIST> ();
	auto layered6 = CreateLayeredCache<int, 4, 5, CONTAINER_TYPE::LIST, CONTAINER_TYPE::VECTOR> ();
	auto layered7 = CreateLayeredCache<int, 4, 5, CONTAINER_TYPE::LIST, CONTAINER_TYPE::ARRAY> ();
	auto layered8 = CreateLayeredCache<int, 4, 5, CONTAINER_TYPE::ARRAY, CONTAINER_TYPE::ARRAY> ();

	return 0;
}