#pragma once
#include <unordered_map>
#include <list>
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
		auto hit = m_hash.find(key);
		if (hit == m_hash.end())
		{
			AddElement(key, element);
		}

		hit->second->second = element;
	}

	std::optional<ElementT> GetElement(KeyT key) const
	{
		auto it = m_hash.find(key);

		if (it == m_hash.end())
		{
			return std::nullopt;
		}

		return it->second->second;
	}

private:
	void AddElement(KeyT key, const ElementT& element)
	{
		if (IsFull())
		{
			DeleteElements();
		}
		
		m_cache.emplace_front(key, element);
		m_hash.emplace(key, std::find_if(m_cache.begin(), m_cache.end(), [key](const auto& element) { return element.first == key; }));
	}

	void DeleteElements()
	{
		/*auto minPriority = m_cache.rend()->priority;
		for (auto it = m_cache.rbegin(); it != m_cache.rend() && it->priority == minPriority; it++)
		{
			if (it->priority == minPriority)
			{
				m_cache.pop_back();
			}
		}*/
	}

	using ListIt = typename std::list<std::pair<KeyT, ElementT>>::iterator;
	size_t m_size;
	std::list<std::pair<KeyT, ElementT>> m_cache;
	std::unordered_map<KeyT, ListIt> m_hash;
};

} // namespace lfu_cache