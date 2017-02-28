//
// Created by iskor on 28/02/2017.
//

#include <unordered_map>
#include <atomic>

#ifndef CPP_BIGRAMS_CONCURRENTUNORDEREDMAP_HPP
#define CPP_BIGRAMS_CONCURRENTUNORDEREDMAP_HPP

#endif //CPP_BIGRAMS_CONCURRENTUNORDEREDMAP_HPP

template<typename type>
class ConcurrentUnorderedIntMap {
private:
    std::unordered_map<type, std::atomic_int> unorderedMap;
    std::mutex mutex;
public:
    void add(const type &key) {
        unorderedMap.at(key)++;
    }

    void insert(const type &key) {
        std::lock_guard<std::mutex> guard{mutex};
        unorderedMap[key]++;
    }
};