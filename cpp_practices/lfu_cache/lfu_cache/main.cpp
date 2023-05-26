#include <vector>
#include <iostream>
#include "LFUCache.h"

int main()
{
	size_t size = 5;
	lfu_cache::LFUCache<int, int> cache{size};
	cache.SetElement(1, 2);
	cache.SetElement(2, 3);
	std::cout << cache.IsFull() << std::endl;
	std::cout << cache.GetElement(1).value() << std::endl;
	std::cout << cache.GetElement(2).value() << std::endl;
}