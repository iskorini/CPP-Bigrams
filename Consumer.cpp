//
// Created by iskor on 19/02/2017.
//

#include <unordered_map>
#include "Consumer.h"
#include <string>
using namespace std;

ctpl::thread_pool Consumer::thread_pool(4);
void Consumer::consume() {
    while (fileQueue.size_approx() > 0 && q.size_approx() > 0) {
        cout << "il consumatore: dimensione coda "<< fileQueue.size_approx()<<endl;
        thread_pool.push([this](int id, moodycamel::BlockingConcurrentQueue<std::vector<std::string>> *&queue, std::unordered_map <std::string, int> &b) {
            this->calcBigrams(id, queue, b);
        }, &q, bigrams);
    }
}

void Consumer::calcBigrams(int id, moodycamel::BlockingConcurrentQueue<std::vector<std::string>> *&queue, std::unordered_map <std::string, int> &b) {
    std::vector<std::string> text;
    unordered_map <std::string, int> m;
    queue->try_dequeue(text);
    //queue.try_dequeue(text);
    std::string bigram = "";
    std::string inv_bigram = "";
    for(int i = 0;i < text.size()-1;i++){
        bigram = text[i]+" "+text[i+1];
        inv_bigram = text[i+1]+" "+text[i];
        if(m.find(bigram) != m.end()){
            m[bigram]++;
        } else if(m.find(inv_bigram) != m.end()){
            m[inv_bigram]++;
        } else{
            m[bigram] = 1;
        }
    }

    std::string inv_key = "";
    vector<std::string> inv_key_split(2);

    mtx.lock();

    for(auto elem : m){
        inv_key = elem.first;
        int counter = elem.second;
        stringstream ssin(inv_key);
        ssin >> inv_key_split[0];
        ssin >> inv_key_split[1];
        inv_key = inv_key_split[1]+" "+inv_key_split[0];

        if(b.find(elem.first) != b.end()){

            b[elem.first] = b[elem.first] + counter;
        } else if(b.find(inv_bigram) != b.end()){
            b[inv_bigram] = b[inv_bigram] + counter;
        } else{
            b[elem.first] = 1;
        }
    }

    cout <<"risultato attuale"<<endl;

    for(auto elem : b){
        cout <<elem.first<<" "<<elem.second<<endl;
    }

    mtx.unlock();

    //cout << text[1] << endl;
}
