//
// Created by iskor on 19/02/2017.
//

#include <iostream>
#include <sstream>
#include "Consumer.h"


using namespace std;


void Consumer::consume(int threadNumber, int maxSize) {
    ctpl::thread_pool thread_pool(threadNumber);
    bool resized = false;
    for (int i = 0; i < expectedFiles; i++) {
        thread_pool.push([this, maxSize, &thread_pool, &resized](int id) {
            this->calcBigrams(id, maxSize, &thread_pool, &resized);
        });
    }
    thread_pool.stop(true);
    bigrams.writeHtmlFile("/home/cecca/ClionProjects/CPP-Bigrams/File/bigrammi.html", 1000);
}

void Consumer::calcBigrams(int id, int maxSize, ctpl::thread_pool *threadPool, bool *resized) {
    std::unique_lock<std::mutex> lock(*m);
    std::vector<std::string> text;
    unordered_map<Key, int, KeyHasher> m;
    if (!(*resized) && *done) {
        threadPool->resize(maxSize);
        *resized = 1;
    }
    while (!(*done || *notified)) {
        cv->wait(lock);

    }
    q.try_dequeue(text);
    *notified = false;

    for(int i = 0;i < text.size()-1;i++){
        Key bigram(text[i], text[i + 1]);
        if(m.find(bigram) != m.end()){
            m[bigram]++;
        } else{
            m[bigram] = 1;
        }
    }

    for(auto elem : m){
        int counter = elem.second;
        if (bigrams.find(elem.first) != bigrams.end()) {
            bigrams.insertAndIncrement(elem.first, counter);
        }else{
            bigrams.insertAndSet(elem.first, 1);
        }

    }

}
