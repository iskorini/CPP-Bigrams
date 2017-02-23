//
// Created by iskor on 19/02/2017.
//

#include <boost/iostreams/device/mapped_file.hpp>
#include "boost/filesystem.hpp"

#include "Producer.h"

using namespace std;

ctpl::thread_pool Producer::thread_pool(4);

void Producer::test_method() {
    thread_pool.push([](int id) {
        cout << "ciao da " << id << endl;
    });
}

void Producer::produce() {
    cout << "ci sono " << fileQueue.size_approx() << " files da processare" << endl;

    while (fileQueue.size_approx() > 0) {
        boost::filesystem::path tmpPath;
        fileQueue.try_dequeue(tmpPath);
        thread_pool.push([](int id, moodycamel::ConcurrentQueue<boost::filesystem::path> *&fileQueue,
                            moodycamel::BlockingConcurrentQueue<std::vector<std::string>> *&q) {
            cout << "blodo" << endl;
            std::vector<std::string> producerUnit;
            boost::filesystem::path path;
            fileQueue->try_dequeue(path);
            boost::iostreams::mapped_file file(path);
            string readFile = file.data();
            std::string word;

            // per prendere il testo solo nella lingua desiderata e levare la parte di intestazione di
            // file provenienti da gutenberg project si parte da 1600 e si finisce 20000 caratteri prima

            for (int i = 1600; i < readFile.size() - 20000; i++) {
                while (' ' != readFile[i]) {
                    word += readFile[i];
                    i++;
                }
                producerUnit.push_back(word);
                word = "";
            }
            q->enqueue(producerUnit);
        }, &fileQueue, &q);

    }


}

Producer::~Producer() {
    thread_pool.~thread_pool();
}

void Producer::elaborateText(int id, moodycamel::ConcurrentQueue<boost::filesystem::path> *&fileQueue) {
    std::vector<std::string> producerUnit;
    boost::filesystem::path path;
    fileQueue->try_dequeue(path);
    boost::iostreams::mapped_file file(path);
    string readFile = file.data();
    std::string word;
    /*
     * per prendere il testo solo nella lingua desiderata e levare la parte di intestazione di
     * file provenienti da gutenberg project si parte da 1600 e si finisce 20000 caratteri prima
     */
    for (int i = 1600; i < readFile.size() - 20000; i++) {
        while (' ' != readFile[i]) {
            word += readFile[i];
            i++;
        }
        producerUnit.push_back(word);
        word = "";
    }
    q.enqueue(producerUnit);
}






