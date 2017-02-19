//
// Created by iskor on 19/02/2017.
//

#ifndef CPP_BIGRAMS_CONSUMER_H
#define CPP_BIGRAMS_CONSUMER_H


#include <string>
#include <boost/lockfree/queue.hpp>
#include <boost/thread/mutex.hpp>

class Consumer {

private:
    boost::lockfree::queue<std::string *>& q;
    std::atomic_int *fileQueueSize;
    std::atomic_int *qSize;
public:
    Consumer(boost::lockfree::queue<std::string *> &q, std::atomic_int *fileQueueSize, std::atomic_int *qSize);
    void consume(int id);
};


#endif //CPP_BIGRAMS_CONSUMER_H
