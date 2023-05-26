#pragma once

namespace lfu_cache
{

template <class Element, class Key = int>
class LFUCache
{
public:
	LFUCache(size_t size);

	size_t GetCacheSize(Key key) const;

	void SetElement(Key key, const Element& element);

private:
	size_t m_size;
};

} // namespace lfu_cache
