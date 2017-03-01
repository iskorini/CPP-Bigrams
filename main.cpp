
#include <iostream>
#include <boost/foreach.hpp>
#include <boost/filesystem.hpp>
#include "Producer.h"
#include "Consumer.h"
#include "boost/iostreams/device/mapped_file.hpp"
#include "ConcurrentUnorderedIntMap.hpp"

using namespace std;
namespace fs =boost::filesystem;
namespace cq = moodycamel;

int main(int argc, char **argv) {
    moodycamel::ConcurrentQueue<boost::filesystem::path> fileQueue(999);
    moodycamel::BlockingConcurrentQueue<std::vector<std::string>> q(999);

    ConcurrentUnorderedIntMap<std::string> bigrams;

    fs::path targetDir("C:\\Users\\Tommaso\\CLionProjects\\CPP-Bigrams\\File\\esempi");
    fs::directory_iterator it(targetDir), eod;

    BOOST_FOREACH(fs::path const &p, std::make_pair(it, eod)) {
                    if (fs::is_regular_file(p)) {
                        //cout << p << endl;
                        fileQueue.enqueue(p);
                    }
                }


    Producer producer(q, fileQueue);
    Consumer consumer(q, fileQueue, (int) fileQueue.size_approx());
    std::thread threadProducer = producer.startProducer();
    std::thread threadConsumer = consumer.startConsumer();
    threadProducer.join();
    threadConsumer.join();

    std::vector<std::string> stringa;

    /*
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

    std:cerr<<"Error "<<strerror(errno)<<std::endl;
    //cout << fileQueue.size_approx() << endl;
    //cout << q.size_approx() << endl;
    bigrams.writeHtmlFile("C:\\Users\\Tommaso\\CLionProjects\\CPP-Bigrams\\Bigrams.html");
    bigrams.printContent();

    return 0;
}
