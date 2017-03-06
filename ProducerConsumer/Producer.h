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
    cq::ConcurrentQueue<std::vector<std::string>> &q;
    cq::ConcurrentQueue<boost::filesystem::path> &fileQueue;
    static ctpl::thread_pool thread_pool;
    std::mutex *m;
    std::condition_variable *cv;
    bool *done;
    bool *notified;
    void elaborateText(int id, moodycamel::ConcurrentQueue<boost::filesystem::path> *&fileQueue,
                       moodycamel::ConcurrentQueue<std::vector<std::string>> *&q);

public:
    Producer(moodycamel::ConcurrentQueue<std::vector<std::string>> &q,
             moodycamel::ConcurrentQueue<boost::filesystem::path> &fileQueue, std::mutex *m, std::condition_variable *cv,
             bool *done, bool *notified) : q(q), fileQueue(fileQueue), m(m), cv(cv), done(done), notified(notified) {}

    void produce(int threadNumber);

    std::thread startProducer(int threadNumber) {
        return std::thread([this, threadNumber] {
            this->produce(threadNumber);
        });
    }
};


#endif //CPP_BIGRAMS_PRODUCER_H
