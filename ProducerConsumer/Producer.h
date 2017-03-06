//
// Created by iskor on 19/02/2017.
//

#ifndef CPP_BIGRAMS_PRODUCER_H
#define CPP_BIGRAMS_PRODUCER_H


#include <string>
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>
#include "../ThreadPool/ctpl.h"
#include "../DataStructure/concurrentqueue.h"
#include "../DataStructure/blockingconcurrentqueue.h"
#include "boost/filesystem.hpp"

using namespace std;
namespace cq = moodycamel;

class Producer {
private:
    cq::BlockingConcurrentQueue<std::vector<std::string>> &q;
    cq::ConcurrentQueue<boost::filesystem::path> &fileQueue;
    static ctpl::thread_pool thread_pool;

    int elaborateText(int id, moodycamel::ConcurrentQueue<boost::filesystem::path> *&fileQueue,
                       moodycamel::BlockingConcurrentQueue<std::vector<std::string>> *&q);

public:
    Producer(moodycamel::BlockingConcurrentQueue<std::vector<std::string>> &q,
             moodycamel::ConcurrentQueue<boost::filesystem::path> &fileQueue) : q(q), fileQueue(fileQueue) {}

    void produce(int threadNumber);

    std::thread startProducer(int threadNumber) {
        std::thread thread1(produce, this, threadNumber);
        return thread1;
    }
};


#endif //CPP_BIGRAMS_PRODUCER_H
