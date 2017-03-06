//
// Created by iskor on 19/02/2017.
//

#include <boost/iostreams/device/mapped_file.hpp>
#include <boost/token_functions.hpp>
#include <boost/tokenizer.hpp>
#include "boost/filesystem.hpp"

#include "Producer.h"

using namespace std;


void Producer::produce(int threadNumber) {
    ctpl::thread_pool thread_pool(threadNumber);
    while (fileQueue.size_approx() > 0) {
        thread_pool.push(
                [this](int id, moodycamel::ConcurrentQueue<boost::filesystem::path> *&fileQueue,
                       moodycamel::BlockingConcurrentQueue<std::vector<std::string>> *&q) {
                    this->elaborateText(id, fileQueue, q);
                }, &fileQueue, &q);
    }
    thread_pool.stop(true);
}

int Producer::elaborateText(int id, moodycamel::ConcurrentQueue<boost::filesystem::path> *&fileQueue,
                             moodycamel::BlockingConcurrentQueue<std::vector<std::string>> *&q) {

    boost::filesystem::path path;

    fileQueue->try_dequeue(path);
    int k = 0;
    boost::iostreams::mapped_file file(path);
    string readFile = file.data();
    std::string word;
    std::vector<std::string> producerUnit;
    producerUnit.reserve(readFile.size());
    typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
    boost::char_separator<char> sep{" ,.;-<>_()[]{}"};
    tokenizer tok{readFile, sep};
    for (const auto &t : tok) {
        producerUnit.push_back(t);
    }
    q->enqueue(producerUnit);
    return 0;
}






