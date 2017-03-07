//
// Created by iskor on 19/02/2017.
//

#ifndef CPP_BIGRAMS_CONSUMER_H
#define CPP_BIGRAMS_CONSUMER_H


#include <string>
#include <unordered_map>
#include <boost/filesystem/path.hpp>
#include "../ThreadPool/ctpl.h"
#include "../DataStructure/blockingconcurrentqueue.h"
#include "../DataStructure/ConcurrentUnorderedIntMap.hpp"
#include <boost/functional/hash.hpp>


struct Key {
    std::string first;
    std::string second;

    Key() {}

    Key(const std::string &first, const std::string &second) : first(first), second(second) {}

    const std::string &getFirst() const {
        return first;
    }

    const std::string &getSecond() const {
        return second;
    }

    void setValue(std::string first, std::string second) {
        first = first;
        second = second;
    }

    bool operator==(const Key &other) const {
        return (first == other.first
                && second == other.second);
    }
};

namespace std {
    template<>
    struct hash<Key> {
        std::size_t operator()(const Key &k) const {
            using std::size_t;
            using std::hash;
            using std::string;

            return ((hash<string>()(k.first)
                     ^ (hash<string>()(k.second) << 1)) >> 1);
        }
    };
}

struct KeyHasher {
    std::size_t operator()(const Key &k) const {
        using boost::hash_value;
        using boost::hash_combine;
        std::size_t seed = 0;
        hash_combine(seed, hash_value(k.first));
        hash_combine(seed, hash_value(k.second));
        return seed;
    }
};


class Consumer {


private:

    moodycamel::ConcurrentQueue<std::vector<std::string>> &q;
    moodycamel::ConcurrentQueue<boost::filesystem::path> &fileQueue;
    ConcurrentUnorderedIntMap<Key, KeyHasher> bigrams;
    int expectedFiles;

    void calcBigrams(int id, int maxSize, ctpl::thread_pool *threadPool, bool *resized);
    std::mutex* m;
    std::condition_variable* cv;
    bool *done;
    bool *notified;


public:


    Consumer(moodycamel::ConcurrentQueue<std::vector<std::string>> &q,
             moodycamel::ConcurrentQueue<boost::filesystem::path> &fileQueue, int expectedFiles, std::mutex *m,std::condition_variable *cv, bool *done, bool *notified) : q(q),
                                                                                                   fileQueue(fileQueue),
                                                                                                   expectedFiles(
                                                                                                           expectedFiles), m(m), cv(cv), done(done), notified(notified) {}

    void consume(int threadNumber, int maxSize);

    std::thread startConsumer(int threadNumber, int maxSize) {
        return std::thread([this, threadNumber, maxSize] {
            this->consume(threadNumber, maxSize);
        });
    }
};


#endif //CPP_BIGRAMS_CONSUMER_H
