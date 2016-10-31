#include <unordered_map>
#include <list>

namespace util {

template <
    typename K,
    typename V,
    typename H = std::hash<K>,
    typename KeyEqual = std::equal_to<K>>
class lru_cache {
private:
    using queue_type = std::list<K>;
    using queue_iterator = typename std::list<K>::iterator;
    using map_type = std::unordered_map<K, std::pair<V, queue_iterator>, H, KeyEqual>;
    using map_iterator = typename map_type::iterator;

    enum { DEFAUL_MAX_SIZE = 25000 };

    // TODO: Add iterators in LIFO order

public:
    using key_type = K;
    using mapped_type = V;
    using value_type = typename map_type::value_type;

    explicit lru_cache(int max_size = DEFAUL_MAX_SIZE) : m_max_size(max_size) { }

    std::pair<map_iterator, bool> insert(const std::pair<K, V>& p) {
        auto it = m_map.find(p.first);
        if (it == m_map.end()) {
            if (m_map.size() == m_max_size) {
                // evict the oldest value
                m_map.erase(m_list.back());
                m_list.pop_back();
            }

            m_list.push_front(p.first);
            return m_map.insert(value_type(p.first, std::make_pair(p.second, m_list.begin())));
        }

        // update value
        it->second.first = p.second;

        m_list.splice(m_list.begin(), m_list, it->second.second);
        it->second.second = m_list.begin();
        return std::make_pair(it, false);
    }

    map_iterator find(const K& key) {
        auto it = m_map.find(key);
        if (it == m_map.end()) {
            return m_map.end();
        }

        m_list.splice(m_list.begin(), m_list, it->second.second);
        it->second.second = m_list.begin();
        return it;
    }

    map_iterator begin() {
        return m_map.begin();
    }

    map_iterator end() {
        return m_map.end();
    }

private:
    map_type m_map;
    queue_type m_list;
    int m_max_size = DEFAUL_MAX_SIZE;
};

} // namespace util
