//
// Created by iskor on 19/02/2017.
//

#ifndef CPP_BIGRAMS_CONSUMER_H
#define CPP_BIGRAMS_CONSUMER_H


#include <string>
#include <boost/thread/mutex.hpp>
#include "concurrentqueue.h"
#include "ctpl.h"
#include "blockingconcurrentqueue.h"

namespace cq = moodycamel;
class Consumer {

private:
    cq::BlockingConcurrentQueue<std::string> &q;
    static ctpl::thread_pool thread_pool;

public:
    Consumer(moodycamel::BlockingConcurrentQueue<std::string> &q);

    void consume();
};


#endif //CPP_BIGRAMS_CONSUMER_H
