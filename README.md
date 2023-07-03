# LRU Cache
Simple C++ static library implementing a LRU cache.

#### Components
The LRU cache works with an underlying LRU container. The implemented LRU containers are **LIST**, **VECTOR** and **ARRAY**. An interface for a LRU container is also exposed for further extension.
There is also a two-layered LRU cache that uses 2 containers. This can be customised with a _Promoter_ that handles the LRU policy between the 2 layers.
Tested with Google tests.
The containers and cache only work for **COPYABLE** objects.

## Usage
Use **CacheHelper** to simplify creation of containers and cache.
```cpp
#include <LRUCache/CacheHelper.hpp>

cache::container::ListLRUContainer<int> contList;
auto contVect = cache::container::CreateContainer<double, CONTAINER_TYPE::VECTOR>();
//must specify size for array container
auto contArray = cache::container::CreateContainer<float, CONTAINER_TYPE::ARRAY, 5>();

//default cache is with list container
cache::LRUCache<int, 50> cacheListCont;
auto cacheVectCont = cache::CreateCache<double, 20, CONTAINER_TYPE::VECTOR>();

//default layered cache is with first layer Vector and second layer List
cache::LayeredLRUCache<int, 10, 50>  layeredCache;
auto layeredCache2 = cache::CreateLayeredCache<double, 4, 10, CONTAINER_TYPE::ARRAY, CONTAINER_TYPE::VECTOR>(); //or any combination
```
The **get** operation is used to retrieve a value by key from the cache or modify one in-place. If a key doesn't exist, it throws an error (use _contains_ to check). 
The **put** operation inserts or moves a value with a corresponding key. If the key already exists, putting a value with the same key doesn't to anything (use _contains_ to check).

```cpp
//must be copyable
struct A{};
A a1;

auto cache = cache::CreateCache<A, 20>();
//put as copy
cache.put(1, a1);
//put temp
cache.put(2, A());
//move
cache.put(3, std::move(a1));

if(cache.contains(1))
{
    //get copy
    A a2 = cache.get(1);
    //get modifiable ref
    A& a3 = cache.get(1);
}
```