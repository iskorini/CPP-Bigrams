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
#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>

using namespace std;
namespace cq = moodycamel;

class Producer {
private:
    static cq::BlockingConcurrentQueue<std::vector<std::string>> &q;
    cq::ConcurrentQueue<boost::filesystem::path> &fileQueue;
    static ctpl::thread_pool thread_pool;

    static void elaborateText(int id, const boost::filesystem::path & path);

public:
    /*Producer(moodycamel::BlockingConcurrentQueue<std::vector<std::string>> &q,
             moodycamel::ConcurrentQueue<boost::filesystem::path> &fileQueue) : q(q), fileQueue(fileQueue) {}*/

    Producer(moodycamel::ConcurrentQueue<boost::filesystem::path> &fileQueue) : fileQueue(fileQueue) {}

    virtual ~Producer();

    void produce();
    void test_method();

};


#endif //CPP_BIGRAMS_PRODUCER_H
