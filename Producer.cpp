//
// Created by iskor on 19/02/2017.
//

#include <boost/iostreams/device/mapped_file.hpp>
#include <boost/token_functions.hpp>
#include <boost/tokenizer.hpp>
#include "boost/filesystem.hpp"

#include "Producer.h"

using namespace std;

ctpl::thread_pool Producer::thread_pool(2);

void Producer::produce() {

    while (fileQueue.size_approx() > 0) {
        thread_pool.push(
                [this](int id, moodycamel::ConcurrentQueue<boost::filesystem::path> *&fileQueue,
                       moodycamel::BlockingConcurrentQueue<std::vector<std::string>> *&q) {
                    this->elaborateText(id, fileQueue, q);
                }, &fileQueue, &q);
    }
    thread_pool.stop(true);
}

void Producer::elaborateText(int id, moodycamel::ConcurrentQueue<boost::filesystem::path> *&fileQueue,
                             moodycamel::BlockingConcurrentQueue<std::vector<std::string>> *&q) {

    boost::filesystem::path path;

    fileQueue->try_dequeue(path);
    int k = 0;
    //printf("porcodio: %d\n",fileQueue->size_approx());
    boost::iostreams::mapped_file file(path);
    string readFile = file.data();
    //cout<<readFile<<endl;
    std::string word;
    std::vector<std::string> producerUnit;
    producerUnit.reserve(readFile.size());
    // per prendere il testo solo nella lingua desiderata e levare la parte di intestazione di
    // file provenienti da gutenberg project si parte da 1600 e si finisce 20000 caratteri prima
    /*
    for (int i = 1600; i < readFile.size() - 20000; i++) {
        while ((readFile[i] >= 'A' && readFile[i] <= 'Z') || ((readFile[i] >= 'a' && readFile[i] <= 'z')))) {
            if(readFile[i] >= 'A' && readFile[i] <= 'Z'){
                readFile[i] = readFile[i]+32;
            }
            word += readFile[i];
            i++;
        }
        if(word != ""){
            producerUnit.push_back(word);
            k++;
        }
        word = "";
    }
    producerUnit.resize(k);

*/
    typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
    boost::char_separator<char> sep{" ,.;-<>_()[]{}"};
    tokenizer tok{readFile, sep};
    for (const auto &t : tok) {
        producerUnit.push_back(t);
        k++;
    }
    q->enqueue(producerUnit);
    cout << "numero di parole: " << k << endl;
}

Producer::~Producer() {
    thread_pool.~thread_pool();
}







