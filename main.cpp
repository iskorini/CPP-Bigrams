
#include <iostream>
#include <boost/foreach.hpp>
#include <boost/filesystem.hpp>
#include "ProducerConsumer/Producer.h"
#include "ProducerConsumer/Consumer.h"
#include "boost/iostreams/device/mapped_file.hpp"
#include <boost/container/vector.hpp>
#include "DataStructure/ConcurrentUnorderedIntMap.hpp"
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/timer/timer.hpp>
using namespace std;
namespace fs =boost::filesystem;
namespace cq = moodycamel;


int main(int argc, char **argv) {
    moodycamel::ConcurrentQueue<boost::filesystem::path> fileQueue(999);
    moodycamel::BlockingConcurrentQueue<std::vector<std::string>> q(999);

    fs::path targetDir("C:\\Users\\iskor\\CLionProjects\\CPP-Bigrams\\File\\Italiano");
    fs::directory_iterator it(targetDir), eod;
    std::vector<std::thread> threadVector;
    BOOST_FOREACH(fs::path const &p, std::make_pair(it, eod)) {
                    if (fs::is_regular_file(p)) {
                        fileQueue.enqueue(p);
                    }
                }
    boost::timer::auto_cpu_timer t;

    Producer producer(q, fileQueue);
    Consumer consumer(q, fileQueue, (int) fileQueue.size_approx());
    std::thread threadProducer = producer.startProducer(8);
    std::thread threadConsumer = consumer.startConsumer(2);
    threadProducer.join();
    threadConsumer.join();
    return 0;
}
