//
// Created by iskor on 19/02/2017.
//

#include <iostream>
#include <sstream>
#include "Consumer.h"

using namespace std;

ctpl::thread_pool Consumer::thread_pool(4);
void Consumer::consume() {
    for (int i = 0; i < expectedFiles; i++) {
        thread_pool.push([this](int id) {
            this->calcBigrams(id);
        });
    }
}

void Consumer::calcBigrams(int id) {
    std::vector<std::string> text;
    unordered_map <std::string, int> m;
    q.try_dequeue(text);
    printf("merda\n");
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

    int z =665;
    printf("%d\n",z);

    int x =666;
    printf("%d\n",x);


    /*
    cout <<"risultato locale"<<endl;
    char* stringa;
    for(auto elem : m){
        strcpy(stringa,elem.first.c_str());
        printf("coppia chiave-valore: %s %d \n",stringa, elem.second);
        //cout <<elem.first<<" "<<elem.second<<endl;
    }
    printf("\n");
    */
    std::string inv_key = "";
    vector<std::string> inv_key_split(2);
    for(auto elem : m){
        inv_key = elem.first;
        int counter = elem.second;
        stringstream ssin(inv_key);
        ssin >> inv_key_split[0];
        ssin >> inv_key_split[1];
        inv_key = inv_key_split[1]+" "+inv_key_split[0];
        if (bigrams.find(elem.first) != bigrams.end()) {
            bigrams.insertAndIncrement(elem.first, counter);
        } else if (bigrams.find(inv_bigram) != bigrams.end()) {
            bigrams.insertAndIncrement(inv_bigram, counter);
        } else{
            bigrams.insertAndSet(elem.first, 1);
        }
    }

    std::cout << "risultato attuale" << std::endl;
    /*
    for(auto elem : b){
        strcpy(stringa,elem.first.c_str());
        printf("coppia chiave-valore: %s %d \n",stringa, elem.second);
        //cout <<elem.first<<" "<<elem.second<<endl;
    }
    printf("\n");
    */
}
