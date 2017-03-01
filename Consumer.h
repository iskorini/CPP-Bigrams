//
// Created by iskor on 19/02/2017.
//

#ifndef CPP_BIGRAMS_CONSUMER_H
#define CPP_BIGRAMS_CONSUMER_H


#include <string>
#include <unordered_map>
#include <boost/filesystem/path.hpp>
#include "ctpl.h"
#include "blockingconcurrentqueue.h"
#include "ConcurrentUnorderedIntMap.hpp"


class Consumer {

private:
    moodycamel::BlockingConcurrentQueue<std::vector<std::string>> &q;
    moodycamel::ConcurrentQueue<boost::filesystem::path> &fileQueue;
    ConcurrentUnorderedIntMap<std::string> &bigrams;
    std::mutex mtx;
    int expectedFiles;
    static ctpl::thread_pool thread_pool;

    void calcBigrams(int id, moodycamel::BlockingConcurrentQueue<std::vector<std::string>> *&queue,
                     ConcurrentUnorderedIntMap<std::string> &bigrams);
public:
    Consumer(moodycamel::BlockingConcurrentQueue<std::vector<std::string>> &q, moodycamel::ConcurrentQueue<boost::filesystem::path> &fileQueue,
             ConcurrentUnorderedIntMap<std::string> &bigrams, int expectedFiles) : q(q), fileQueue(fileQueue),
                                                                                   bigrams(bigrams),
                                                                                   expectedFiles(expectedFiles) {}
    void consume();
    std::thread startConsumer() {
        return std::thread([this] {
            this->consume();
        });
    }
};


#endif //CPP_BIGRAMS_CONSUMER_H
