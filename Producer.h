//
// Created by iskor on 19/02/2017.
//

#ifndef CPP_BIGRAMS_PRODUCER_H
#define CPP_BIGRAMS_PRODUCER_H


#include <string>
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>
#include "ctpl.h"
#include "concurrentqueue.h"
#include "blockingconcurrentqueue.h"
#include "boost/filesystem.hpp"

using namespace std;
namespace cq = moodycamel;

class Producer {
private:
    cq::BlockingConcurrentQueue<std::vector<std::string>> &q;
    cq::ConcurrentQueue<boost::filesystem::path> &fileQueue;
    static ctpl::thread_pool thread_pool;

    void elaborateText(int id, moodycamel::ConcurrentQueue<boost::filesystem::path> *&fileQueue,
                       moodycamel::BlockingConcurrentQueue<std::vector<std::string>> *&q);

public:
    Producer(moodycamel::BlockingConcurrentQueue<std::vector<std::string>> &q,
             moodycamel::ConcurrentQueue<boost::filesystem::path> &fileQueue) : q(q), fileQueue(fileQueue) {}
    void produce();

    virtual ~Producer();
    std::thread startProducer() {
        return std::thread([this] {
            this->produce();
        });
    }
};


#endif //CPP_BIGRAMS_PRODUCER_H
