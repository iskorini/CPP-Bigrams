
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


void prova2(std::string fileData){
    boost::container::vector<string> elaboratedFile;
    boost::char_separator<char> sep("1234567890.;:)(*',_?!-#$%&[]{}<>/|=+£^°§@~\t\n\\\r\'\"\a\f\b\v ");
    boost::tokenizer<boost::char_separator<char>> tokens(fileData, sep);

    BOOST_FOREACH(string s, tokens){
                    boost::algorithm::to_lower(s);
                    elaboratedFile.push_back(s);
                }
    //elaboratedFiles.push(elaboratedFile);
}


void prova(std::string readFile) {
    //cout << "sono il thread n: "<<std::this_thread::get_id()<<endl;
    __thread std::vector<std::string> producerUnit;
    std::string word;
    for (int i = 0; i < readFile.size(); i++) {
        while (/*' ' != readFile[i] && '\n' != readFile[i] && */((readFile[i] >= 'A' && readFile[i] <= 'Z') || ((readFile[i] >= 'a' && readFile[i] <= 'z')))) {
            if(readFile[i] >= 'A' && readFile[i] <= 'Z'){
                readFile[i] = readFile[i]+32;
            }
            word += readFile[i];
            i++;
        }
        if(word != ""){
            producerUnit.push_back(word);
        }
        word = "";
    }
    //cout <<std::this_thread::get_id()<< " HO FINITO PORCAMADONNA" << endl;
    //q->enqueue(producerUnit);
}


int main(int argc, char **argv) {
    moodycamel::ConcurrentQueue<boost::filesystem::path> fileQueue(999);
    moodycamel::BlockingConcurrentQueue<std::vector<std::string>> q(999);

    fs::path targetDir("C:\\Users\\iskor\\CLionProjects\\CPP-Bigrams\\File\\English");
    fs::directory_iterator it(targetDir), eod;
    std::vector<std::thread> threadVector;
    BOOST_FOREACH(fs::path const &p, std::make_pair(it, eod)) {
                    if (fs::is_regular_file(p)) {
                        //boost::iostreams::mapped_file file(p);
                        //string data = file.data();
                        //cout << file.data() << endl;
                        fileQueue.enqueue(p);
                        //threadVector.push_back(std::thread(prova, data));
                        //file.close();
                    }
                }
    /*
    for (int i = 0; i<threadVector.size(); i++) {
        cout << "ho joinato " << threadVector[i].get_id() << endl;
        threadVector[i].join();
    }*/

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
