
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

int main(int argc, char **argv) {
    moodycamel::ConcurrentQueue<boost::filesystem::path> fileQueue(999);
    moodycamel::BlockingConcurrentQueue<std::vector<std::string>> q(999);

    std::unordered_map <std::string, int> bigrams;

    fs::path targetDir("C:\\Users\\Tommaso\\CLionProjects\\CPP-Bigrams\\File\\esempi");
    fs::directory_iterator it(targetDir), eod;

    BOOST_FOREACH(fs::path const &p, std::make_pair(it, eod)) {
                    if (fs::is_regular_file(p)) {
                        //cout << p << endl;
                        fileQueue.enqueue(p);
                    }
                }

    Producer producer(q, fileQueue);
    Consumer consumer(q, fileQueue, bigrams);
    std::thread threadProducer = producer.startProducer();
    std::thread threadConsumer = consumer.startConsumer();
    threadProducer.join();
    threadConsumer.join();
    delete &producer;
    delete &consumer;

    for(auto elem : bigrams){
        cout <<elem.first<<" "<<elem.second<<endl;
    }

    cout << fileQueue.size_approx() << endl;
    cout << q.size_approx() << endl;
    return 0;
}
