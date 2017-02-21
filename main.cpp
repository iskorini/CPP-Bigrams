
#include <iostream>
#include <string>
#include "ctpl.h"
#include <boost/foreach.hpp>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include "Producer.h"
#include "Consumer.h"
#include <thread>
#include "concurrentqueue.h"
#include "blockingconcurrentqueue.h"
#include "boost/iostreams/device/mapped_file.hpp"

using namespace std;
namespace fs =boost::filesystem;
namespace cq = moodycamel;

void printcc(boost::filesystem::path *merda) {
    cout << *merda << endl;
}
int main(int argc, char **argv) {
    cq::BlockingConcurrentQueue <std::vector<std::string>> q(999);
    cq::ConcurrentQueue <fs::path> fileQueue(999);
    fs::path targetDir("C:\\Users\\iskor\\CLionProjects\\CPP-Bigrams\\File");
    fs::directory_iterator it(targetDir), eod;
    BOOST_FOREACH(fs::path const &p, std::make_pair(it, eod)) {
                    if (fs::is_regular_file(p)) {
                        cout << p << endl;
                        fileQueue.enqueue(p);
                    }
                }

    while (fileQueue.size_approx() > 0) {
        cout << fileQueue.size_approx() << endl;
        fs::path path;
        fileQueue.try_dequeue(path);
        boost::iostreams::mapped_file file(path);
        cout << file.data() << endl;
        cout << path << endl;
    }

    Producer producer(q, fileQueue);
    /*
    Producer producer2(q, fileQueue);
    Producer producer3(q, fileQueue);
    Producer producer4(q, fileQueue);
    Producer producer5(q, fileQueue);
    Producer producer6(q, fileQueue);
    Producer producer7(q, fileQueue);
    Producer producer8(q, fileQueue);
    Producer producer9(q, fileQueue);
    producer1.test_method();
    producer2.test_method();
    producer3.test_method();
    producer4.test_method();
    producer5.test_method();
    producer6.test_method();
    producer7.test_method();
    producer8.test_method();
    producer9.test_method();
    producer2.test_method();
    producer3.test_method();
    producer4.test_method();
    producer5.test_method();
    producer6.test_method();
    producer7.test_method();
    producer8.test_method();
    producer9.test_method();
    producer2.test_method();
    producer3.test_method();
    producer4.test_method();
    producer5.test_method();
    producer6.test_method();
    producer7.test_method();
    producer8.test_method();
    producer9.test_method();
    */
    return 0;
}
