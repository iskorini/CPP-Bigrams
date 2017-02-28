//
// Created by iskor on 19/02/2017.
//

#ifndef CPP_BIGRAMS_CONSUMER_H
#define CPP_BIGRAMS_CONSUMER_H


#include <string>
#include <boost/thread/mutex.hpp>
#include <unordered_map>
#include <bits/unordered_map.h>
#include <boost/filesystem/path.hpp>
#include "ctpl.h"
#include "blockingconcurrentqueue.h"


class Consumer {

private:
    moodycamel::BlockingConcurrentQueue<std::vector<std::string>> &q;
    moodycamel::ConcurrentQueue<boost::filesystem::path> &fileQueue;
    std::unordered_map <std::string, int> &bigrams;
    std::mutex mtx;
    int expectedFiles;
    static ctpl::thread_pool thread_pool;

    void calcBigrams(int id, moodycamel::BlockingConcurrentQueue<std::vector<std::string>> *&queue, std::unordered_map <std::string, int> &bigrams);
public:
    Consumer(moodycamel::BlockingConcurrentQueue<std::vector<std::string>> &q, moodycamel::ConcurrentQueue<boost::filesystem::path> &fileQueue,
             std::unordered_map<std::string, int> &bigrams, int expectedFiles) : q(q), fileQueue(fileQueue),
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
