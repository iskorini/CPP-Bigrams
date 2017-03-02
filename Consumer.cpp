//
// Created by iskor on 19/02/2017.
//

#include <iostream>
#include <sstream>
#include "Consumer.h"

using namespace std;

ctpl::thread_pool Consumer::thread_pool(4);
void Consumer::consume() {
    //printf("diocaro\n");
    for (int i = 0; i < expectedFiles; i++) {
        //printf("%d\n",expectedFiles);
        thread_pool.push([this](int id) {
            this->calcBigrams(id);
        });
    }
    thread_pool.~thread_pool();
    //printf("\n");
    //bigrams.printContent();
    //bigrams.printValue("such as");
    bigrams.writeHtmlFile("C:\\Users\\Tommaso\\CLionProjects\\CPP-Bigrams\\Bigrams.html");
}

void Consumer::calcBigrams(int id) {
    std::vector<std::string> text;
    unordered_map <std::string, int> m;
    q.wait_dequeue(text);
    std::string bigram = "";
    //std::string inv_bigram = "";
    //printf("dimensione del testo %d\n",text.size());
    for(int i = 0;i < text.size()-1;i++){
        bigram = text[i]+" "+text[i+1];
        //inv_bigram = text[i+1]+" "+text[i];
        //printf("abete\n");
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
