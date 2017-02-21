//
// Created by iskor on 19/02/2017.
//

#include "Consumer.h"
using namespace std;

ctpl::thread_pool Consumer::thread_pool(8);

void Consumer::consume() {
/*
    qSize--;
    string *file;
    q.pop(file);
    cout << file << endl; */
}

Consumer::Consumer(moodycamel::BlockingConcurrentQueue<string> &q) : q(q) {}
