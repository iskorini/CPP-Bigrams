//
// Created by iskor on 19/02/2017.
//

#include <boost/iostreams/device/mapped_file.hpp>
#include "boost/filesystem.hpp"

#include "Producer.h"

using namespace std;

ctpl::thread_pool Producer::thread_pool(4);

void Producer::produce() {
    while (fileQueue.size_approx() > 0) {
        thread_pool.push(
                [this](int id, moodycamel::ConcurrentQueue<boost::filesystem::path> *&fileQueue,
                       moodycamel::BlockingConcurrentQueue<std::vector<std::string>> *&q) {
                    this->elaborateText(id, fileQueue, q);
                }, &fileQueue, &q);
    }
}

void Producer::elaborateText(int id, moodycamel::ConcurrentQueue<boost::filesystem::path> *&fileQueue,
                             moodycamel::BlockingConcurrentQueue<std::vector<std::string>> *&q) {
    std::vector<std::string> producerUnit;
    boost::filesystem::path path;

    fileQueue->try_dequeue(path);
    //printf("porcodio: %d\n",fileQueue->size_approx());
    boost::iostreams::mapped_file file(path);
    string readFile = file.data();
    //printf("stringa: %s\n",readFile);
    //cout<<readFile<<endl;
    std::string word;
    // per prendere il testo solo nella lingua desiderata e levare la parte di intestazione di
    // file provenienti da gutenberg project si parte da 1600 e si finisce 20000 caratteri prima
    for (int i = 0 /*1600*/; i < readFile.size() /*- 20000*/; i++) {
        while (' ' != readFile[i]) {
            word += readFile[i];
            i++;
        }
        producerUnit.push_back(word);
        //cout<<"parola estratta: "<<word<<endl;
        word = "";
    }

    q->enqueue(producerUnit);
}

Producer::~Producer() {
    thread_pool.~thread_pool();
}







