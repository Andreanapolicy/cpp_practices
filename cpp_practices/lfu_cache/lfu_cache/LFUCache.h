#pragma once
#include <list>
#include <optional>
#include <unordered_map>

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
		CacheIt it = std::find_if(m_cache.begin(), m_cache.end(), [key](const CacheElement& element) {
			return element.key == key;
		});

		if (it == m_cache.end())
		{
			it->element = element;
			it->priority++;
			return;
		}

		if (IsFull())
		{
			DeleteElements();
		}
		m_cache.emplace_back(key, element);
	}

	std::optional<ElementT> GetElement(KeyT key) const
	{
		CacheIt it = std::find_if(m_cache.begin(), m_cache.end(), [key](CacheElement& element) {
			return element.key == key;
		});

		if (it == m_cache.end())
		{
			return std::nullopt;
		}

		it->priority++;
		return it->element;
	}

private:
	struct CacheElement // TODO: too slow to work with struct for every element.
	{
		KeyT key;
		ElementT element;
		int priority = 1;
	};

	using CacheIt = typename std::list<CacheElement>::iterator;

	/*CacheIt GetElementByKey(KeyT key) const
	{
		return std::find_if(m_cache.begin(), m_cache.end(), [key](const CacheElement& element) {
			return element.key == key;
		});
	}*/

	void DeleteElements()
	{
		auto minPriority = m_cache.rend()->priority;
		for (auto it = m_cache.rbegin(); it != m_cache.rend() && it->priority == minPriority; it++)
		{
			if (it->priority == minPriority)
			{
				m_cache.pop_back();
			}
		}
	}

	size_t m_size;
	std::list<CacheElement> m_cache;
};

} // namespace lfu_cache