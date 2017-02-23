//
// Created by iskor on 19/02/2017.
//

#include "Consumer.h"
using namespace std;

ctpl::thread_pool Consumer::thread_pool(4);
void Consumer::consume() {
    while (q.size_approx() > 0) {
        thread_pool.push([this](int id, moodycamel::BlockingConcurrentQueue<std::vector<std::string>> *&queue) {
            this->calcBigrams(id, queue);
        }, &q);
    }
}

void Consumer::calcBigrams(int id, moodycamel::BlockingConcurrentQueue<std::vector<std::string>> *&queue) {
    std::vector<std::string> text;
    queue->try_dequeue(text);
    //queue.try_dequeue(text);
    cout << text[1] << endl;
}
