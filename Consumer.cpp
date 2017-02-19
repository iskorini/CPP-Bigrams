//
// Created by iskor on 19/02/2017.
//

#include "Consumer.h"
using namespace std;
Consumer::Consumer(boost::lockfree::queue<std::string *> &q, std::atomic_int *fileQueueSize, std::atomic_int *qSize)
        : q(q), fileQueueSize(fileQueueSize), qSize(qSize) {}

void Consumer::consume(int id) {
    qSize--;
    string *file;
    q.pop(file);
    cout << file << endl; //sostituire con calcolo bigrammi
}
