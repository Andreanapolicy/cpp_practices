#define CATCH_CONFIG_MAIN
#include "../../catch2/catch.hpp"
#include "../lfu_cache/lfu_cache/LFUCache.h"

using namespace lfu_cache;

TEST_CASE("check construct")
{
	GIVEN("cache with 5 capacity")
	{
		LFUCache<int, int> cache{5};
		
		WHEN("No activities after creating")
		{
			THEN("Cache will not be full")
			{
				REQUIRE_FALSE(cache.IsFull());
			}
		}
	}

	GIVEN("cache with 0 capacity")
	{
		LFUCache<int, int> cache{0};
		
		WHEN("No activities after creating")
		{
			THEN("Cache will be full")
			{
				REQUIRE(cache.IsFull());
			}
		}
	}
}