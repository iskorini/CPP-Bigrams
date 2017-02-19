//
// Created by iskor on 19/02/2017.
//

#ifndef CPP_BIGRAMS_PRODUCER_H
#define CPP_BIGRAMS_PRODUCER_H


#include <string>
#include "boost/lockfree/queue.hpp"
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>



class Producer {
private:
    std::string path;
    boost::lockfree::queue<std::string *>& q;
    boost::lockfree::queue<std::string *>& fileQueue;
    std::atomic_int *fileQueueSize;
    std::atomic_int *qSize;
    static boost::mutex mtx;

public:
    Producer(const std::string &path, boost::lockfree::queue<std::string *> &q,
             boost::lockfree::queue<std::string *> &fileQueue, std::atomic_int *fileQueueSize, std::atomic_int *qSize);

public:
    void produce(int id);
    void test_method();

};


#endif //CPP_BIGRAMS_PRODUCER_H
