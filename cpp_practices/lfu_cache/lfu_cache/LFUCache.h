#pragma once
#include <list>
#include <unordered_map>
#include <optional>

namespace lfu_cache
{

template <class ElementT, class KeyT = int>
class LFUCache
{
public:
	explicit LFUCache(size_t size)
		: m_size(size)
	{
	}

	bool IsFull() const
	{
		return m_cache.size() == m_size;
	}

	void SetElement(KeyT key, const ElementT& element)
	{
		
	}

	std::optional<ElementT> GetElement(KeyT key) const
	{
		auto it = std::find_if(m_cache.begin(), m_cache.end(), [key](const CacheElement& element) {
			return element.key == key;
		});

		if (it == m_cache.end())
		{
			return std::nullopt_t;
		}

		it->priority++;
		return it->element;
	}

private:
	struct CacheElement
	{
		KeyT key;
		ElementT element;
		int priority;
	};

	size_t m_size;

	std::list<CacheElement> m_cache;
};

} // namespace lfu_cache