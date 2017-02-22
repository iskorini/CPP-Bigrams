//
// Created by iskor on 19/02/2017.
//

#include <iostream>
#include <boost/iostreams/device/mapped_file.hpp>
#include <boost/filesystem/path.hpp>
#include "Producer.h"

using namespace std;

ctpl::thread_pool Producer::thread_pool(8);

moodycamel::BlockingConcurrentQueue<vector<string>> x(999);
moodycamel::BlockingConcurrentQueue<std::vector<std::string>> & Producer::q = x;

void Producer::test_method() {
    thread_pool.push([](int id) {
        cout << "ciao da " << id << endl;
    });
}

void Producer::produce() {
    while (fileQueue.size_approx() > 0) {
        boost::filesystem::path tmpPath;
        fileQueue.try_dequeue(tmpPath);
        thread_pool.push(Producer::elaborateText, tmpPath);
    }
}


void Producer::elaborateText(int id, const boost::filesystem::path & path) {
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
    cout << "ciaone"<< endl;
}

Producer::~Producer() {
    thread_pool.~thread_pool();
}





