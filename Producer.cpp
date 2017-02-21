//
// Created by iskor on 19/02/2017.
//

#include <iostream>
#include <boost/iostreams/device/mapped_file.hpp>
#include <boost/filesystem/path.hpp>
#include "Producer.h"

using namespace std;

ctpl::thread_pool Producer::thread_pool(8);

void Producer::test_method() {
    thread_pool.push([](int id) {
        cout << "ciao da " << id << endl;
    });
}

void Producer::produce() {
    while (fileQueue.size_approx() > 0) {
        boost::filesystem::path tmpPath;
        fileQueue.try_dequeue(tmpPath);
        thread_pool.push(elaborateText, tmpPath);
    }
}

void Producer::elaborateText(int id, boost::filesystem::path path) {
    std::vector<std::string> producerUnit;
    boost::iostreams::mapped_file file(path);
    string readFile = file.data();
    std::string word;
    for (int i = 0; i < readFile.size(); i++) {
        while (' ' != readFile[i]) {
            word += readFile[i];
            i++;
        }
        producerUnit.push_back(word);
        word = "";
    }
    q.enqueue(producerUnit);
}

Producer::~Producer() {
    thread_pool.~thread_pool();
}





