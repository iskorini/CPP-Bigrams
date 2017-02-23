
#include <iostream>
#include "ctpl.h"
#include <boost/foreach.hpp>
#include <boost/filesystem.hpp>
#include "Producer.h"
#include "Consumer.h"
#include "boost/iostreams/device/mapped_file.hpp"

using namespace std;
namespace fs =boost::filesystem;
namespace cq = moodycamel;

void printcc(boost::filesystem::path *merda) {
    cout << *merda << endl;
}

int main(int argc, char **argv) {
    cout << "inizio" << endl;
    moodycamel::ConcurrentQueue<boost::filesystem::path> fileQueue(999);
    moodycamel::BlockingConcurrentQueue<std::vector<std::string>> q(999);
    fs::path targetDir("C:\\Users\\iskor\\CLionProjects\\CPP-Bigrams\\File\\English");
    fs::directory_iterator it(targetDir), eod;
    BOOST_FOREACH(fs::path const &p, std::make_pair(it, eod)) {
                    if (fs::is_regular_file(p)) {
                        cout << p << endl;
                        fileQueue.enqueue(p);
                    }
                }
    cout << "cazzo culo " << fileQueue.size_approx() << endl;
    Producer producer(q, fileQueue);
    std::thread threadProducer = producer.startProducer();
    threadProducer.join();
    //Consumer consumer(q);
    //consumer.consume();
    return 0;
}
