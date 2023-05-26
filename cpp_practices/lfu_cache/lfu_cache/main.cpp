#include <vector>
#include <iostream>
#include "LFUCache.h"

int main()
{
	size_t size = 1;
	lfu_cache::LFUCache<int, int> cache{size};

	std::cout << cache.IsFull() << std::endl;
	cache.SetElement(1, 2);
}