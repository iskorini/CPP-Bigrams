//
// Created by iskor on 19/02/2017.
//

#include <iostream>
#include <sstream>
#include "Consumer.h"


using namespace std;


void Consumer::consume(int threadNumber) {
    ctpl::thread_pool thread_pool(threadNumber);
    for (int i = 0; i < expectedFiles; i++) {
        thread_pool.push([this](int id) {
            this->calcBigrams(id);
        });
    }
    thread_pool.stop(true);
    //bigrams.writeHtmlFile("C:\\Users\\iskor\\CLionProjects\\CPP-Bigrams\\Bigrams.html", 3000);
}

int Consumer::calcBigrams(int id) {
    std::vector<std::string> text;
    unordered_map<Key, int, KeyHasher> m;
    q.wait_dequeue(text);
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

    return 0;
}
