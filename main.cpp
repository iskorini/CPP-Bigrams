
#include <iostream>
#include <boost/foreach.hpp>
#include <boost/filesystem.hpp>
#include "Producer.h"
#include "Consumer.h"
#include "boost/iostreams/device/mapped_file.hpp"
#include <boost/container/vector.hpp>
#include "ConcurrentUnorderedIntMap.hpp"
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
using namespace std;
namespace fs =boost::filesystem;
namespace cq = moodycamel;


int main(int argc, char **argv) {
    moodycamel::ConcurrentQueue<boost::filesystem::path> fileQueue(999);
    moodycamel::BlockingConcurrentQueue<std::vector<std::string>> q(999);

    fs::path targetDir("C:\\Users\\iskor\\CLionProjects\\CPP-Bigrams\\File\\English");
    fs::directory_iterator it(targetDir), eod;
    std::vector<std::thread> threadVector;
    BOOST_FOREACH(fs::path const &p, std::make_pair(it, eod)) {
                    if (fs::is_regular_file(p)) {
                        fileQueue.enqueue(p);
                    }
                }

    Producer producer(q, fileQueue);
    Consumer consumer(q, fileQueue, (int) fileQueue.size_approx());
    std::thread threadProducer = producer.startProducer();
    std::thread threadConsumer = consumer.startConsumer();
    threadProducer.join();
    threadConsumer.join();

    /*
    std:vector<std::string> stringa;
    cout<<"dimensione q: "<<q.size_approx()<<endl;
    for(int i=0;i < 3;i++){
        q.try_dequeue(stringa);
        cout<<"stampo stringa "<<i<<endl;
        for(int j=0;j < stringa.size();j++){
            cout<<stringa[j].c_str()<<endl;
        }
        cout<<endl;
    }
    */

    //cout<<"culo1"<<endl;
    //free(producer);
    //cout<<"culo2"<<endl;
    //delete &consumer;
    /*
    for(auto elem : bigrams){
        cout <<elem.first<<" "<<elem.second<<endl;
    }
     */
    /*
    cout << fileQueue.size_approx() << endl;
    cout << q.size_approx() << endl;
    */
    return 0;
}
