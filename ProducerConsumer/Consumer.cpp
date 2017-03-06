//
// Created by iskor on 19/02/2017.
//

#include <iostream>
#include <sstream>
#include "Consumer.h"


using namespace std;


void Consumer::consume(int threadNumber) {
    ctpl::thread_pool thread_pool(threadNumber);
    //printf("diocaro\n");
    for (int i = 0; i < expectedFiles; i++) {
        //printf("%d\n",expectedFiles);
        thread_pool.push([this](int id) {
            this->calcBigrams(id);
        });
    }
    thread_pool.stop(true);
    //printf("\n");
    //bigrams.printContent();
    //bigrams.printValue("such as");
    bigrams.writeHtmlFile("/home/cecca/ClionProjects/CPP-Bigrams/File/bigrammi.html", 3000);
}

void Consumer::calcBigrams(int id) {
    std::unique_lock<std::mutex> lock(*m);
    std::vector<std::string> text;
    unordered_map<Key, int, KeyHasher> m;


    while (!(*done || *notified)) {
        cv->wait(lock);
        //auto now = std::chrono::system_clock::now();
        //cv->wait_until(lock, now +std::chrono::microseconds(1000));
        //cout << "SONO BLOCCATO CON " <<*done <<*notified <<endl;
    }
    //cout << "blodo" << endl;
    q.try_dequeue(text);
    *notified = false;
    //std::string bigram;

    //std::stringstream bigramStream;
    //printf("dimensione del testo %d\n",text.size());
    for(int i = 0;i < text.size()-1;i++){
        //bigram = text[i]+" "+text[i+1];
        //bigramStream << text[i] << " " << text[i + 1];
        //bigram = bigramStream.str();
        Key bigram(text[i], text[i + 1]);
        //bigram.setValue(text[i], text[i+1]);
        // bigramStream.str("");
        //bigramStream.clear();
        if(m.find(bigram) != m.end()){
            m[bigram]++;
        }/* else if(m.find(inv_bigram) != m.end()){
            m[inv_bigram]++;
        }*/ else{
            m[bigram] = 1;
        }
    }

    /*
    cout <<"risultato locale"<<endl;
    //char* stringa;
    for(auto elem : m){
        //strcpy(stringa,elem.first.c_str());
        printf("coppia chiave-valore: %s %d \n",elem.first.c_str(), elem.second);
        //cout <<elem.first<<" "<<elem.second<<endl;
    }
    printf("\n");
    */

    //std::string inv_key = "";
    //vector<std::string> inv_key_split(2);
    for(auto elem : m){
        //inv_key = elem.first;
        int counter = elem.second;
        //stringstream ssin(inv_key);
        //ssin >> inv_key_split[0];
        //ssin >> inv_key_split[1];
        //inv_key = inv_key_split[1]+" "+inv_key_split[0];
        if (bigrams.find(elem.first) != bigrams.end()) {
            bigrams.insertAndIncrement(elem.first, counter);
        }/* else if (bigrams.find(inv_bigram) != bigrams.end()) {
            bigrams.insertAndIncrement(inv_bigram, counter);
        } */else{
            bigrams.insertAndSet(elem.first, 1);
        }

    }

}
