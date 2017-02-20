//
// Created by iskor on 19/02/2017.
//

#include <iostream>
#include "Producer.h"

using namespace std;

ctpl::thread_pool Producer::thread_pool(8);

void Producer::test_method() {
    /*
    threadPool.enqueue([]{
        cout<<"prova"<<endl;
    });
     */
    thread_pool.push([](int id) {
        cout << "ciao da " << id << endl;
    });
}

void Producer::produce(int id) {
    /*
    while (!fileQueue.empty()) {
        string *file;
        mtx.lock();
        if(*qSize<=9) {
            fileQueue.pop(file);
            fileQueueSize--;
            q.push(file);
            qSize++;
        }
        mtx.unlock();
    }
     */
}

Producer::Producer(const string &path, boost::lockfree::queue<string *> &q, boost::lockfree::queue<string *> &fileQueue,
                   atomic_int *fileQueueSize, atomic_int *qSize) : path(path), q(q), fileQueue(fileQueue),
                                                                   fileQueueSize(fileQueueSize), qSize(qSize) {
}
