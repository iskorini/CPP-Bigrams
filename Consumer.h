//
// Created by iskor on 19/02/2017.
//

#ifndef CPP_BIGRAMS_CONSUMER_H
#define CPP_BIGRAMS_CONSUMER_H


#include <string>
#include <boost/thread/mutex.hpp>
#include "ctpl.h"
#include "blockingconcurrentqueue.h"


class Consumer {

private:
    moodycamel::BlockingConcurrentQueue<std::vector<std::string>> &q;

    static ctpl::thread_pool thread_pool;

    void calcBigrams(int id);
public:
    Consumer(moodycamel::BlockingConcurrentQueue<std::vector<std::string>> &q) : q(q) {}
    void consume();

    std::thread startConsumer() {
        return std::thread([this] {
            this->consume();
        });
    }
};


#endif //CPP_BIGRAMS_CONSUMER_H
