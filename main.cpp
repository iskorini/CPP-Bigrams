
#include <iostream>
#include <string>
#include <queue>
#include "ctpl.h"
#include "boost/lockfree/queue.hpp"
#include <boost/foreach.hpp>
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include "Producer.h"
#include "Consumer.h"
#include <thread>

using namespace std;
namespace fs =boost::filesystem;



int main(int argc, char **argv) {
    boost::lockfree::queue<std::string*> q(999);
    boost::lockfree::queue<std::string *> fileQueue(999);
    std::atomic_int uno(0);
    std::atomic_int due(0);

    fs::path targetDir("C:\\Users\\iskor\\CLionProjects\\CPP-Bigrams\\File");
    fs::directory_iterator it(targetDir), eod;
    BOOST_FOREACH(fs::path const &p, std::make_pair(it, eod)) {
                    if (fs::is_regular_file(p)) {
                        cout << p << endl;
                    }
                }

    Producer producer1("prova", q, fileQueue, &uno, &due);
    Producer producer2("prova", q, fileQueue, &uno, &due);
    Producer producer3("prova", q, fileQueue, &uno, &due);
    Producer producer4("prova", q, fileQueue, &uno, &due);
    Producer producer5("prova", q, fileQueue, &uno, &due);
    Producer producer6("prova", q, fileQueue, &uno, &due);
    Producer producer7("prova", q, fileQueue, &uno, &due);
    Producer producer8("prova", q, fileQueue, &uno, &due);
    Producer producer9("prova", q, fileQueue, &uno, &due);
    producer1.test_method();
    producer2.test_method();
    producer3.test_method();
    producer4.test_method();
    producer5.test_method();
    producer6.test_method();
    producer7.test_method();
    producer8.test_method();
    producer9.test_method();
    return 0;
}
