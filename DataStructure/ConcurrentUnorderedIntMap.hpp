//
// Created by iskor on 28/02/2017.
//

#include <unordered_map>
#include <fstream>
#include <mutex>

#ifndef CPP_BIGRAMS_CONCURRENTUNORDEREDMAP_HPP
#define CPP_BIGRAMS_CONCURRENTUNORDEREDMAP_HPP


template<typename type, typename type2>
class ConcurrentUnorderedIntMap {
private:
    std::unordered_map<type, int, type2> unorderedMap;
    mutable std::mutex mutex;
public:
    ConcurrentUnorderedIntMap() {}

    ConcurrentUnorderedIntMap(ConcurrentUnorderedIntMap &&other) {
        std::lock_guard<std::mutex> lock(other.mutex);
        unorderedMap = std::move(other.unorderedMap);
    }

    ConcurrentUnorderedIntMap(const ConcurrentUnorderedIntMap &other) {
        std::lock_guard<std::mutex> lock(other.mutex);
        unorderedMap = other.unorderedMap;
    }
    void insertAndIncrement(const type &key, int value) {
        std::lock_guard<std::mutex> guard{mutex};
        unorderedMap[key] += value;
    }

    void insertAndSet(const type &key, int value) {
        std::lock_guard<std::mutex> guard(mutex);
        unorderedMap[key] = value;
    }

    typename std::unordered_map<type, int>::const_iterator find(type x) {
        return unorderedMap.find(x);
    };

    typename std::unordered_map<type, int>::const_iterator end() {
        return unorderedMap.end();
    };

    long size() {
        std::lock_guard<std::mutex> guard(mutex);
        return unorderedMap.size();
    };

    /*
     * non thread safe, usare solo per get
     */
    int &operator[](type &key) {
        return unorderedMap[key];
    }

    int &operator[](type *key) {
        return unorderedMap[key];
    }

    /*
     * debug function
    */

    void printContent(){
        std::cout<<"HASHMAP CONCORRENTE"<<std::endl;
        for(auto elem : unorderedMap){
            printf("coppia chiave-valore: %s %s %d\n", elem.first.getFirst().c_str(), elem.first.getSecond().c_str(),
                   elem.second);
            //std::cout <<"coppia chiave-valore:"<<elem.first.c_str()<<" "<<elem.second<<std::endl;
        }
        printf("\n");
    }

    void printValue(std::string key){
        if(unorderedMap.find(key) != unorderedMap.end()){
            printf("Valore: %d\n", unorderedMap[key]);
        }else{
            printf("Chiave non trovata\n");
        }
    }

    void writeHtmlFile(std::string path, int minBigrams) {
        std::ofstream htmlFile;
        htmlFile.open(path);
        htmlFile << "<!DOCTYPE html><html><head></head>";
        htmlFile
                << "<link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0-alpha.6/css/bootstrap.min.css\" integrity=\"sha384-rwoIResjU2yc3z8GV/NPeZWAv56rSmLldC3R/AZzGRnGxQQKnKkoFVhFQhNUwEyJ\" crossorigin=\"anonymous\">";
        htmlFile << "<body>";
        htmlFile << "<h1>Bigrams</h1>";
        htmlFile << "<ul class=\"col-sm-12 list-group\">\n";

        for (auto it = unorderedMap.begin(); it != unorderedMap.end(); ++it) {
            if (it->second >= minBigrams) {
                htmlFile << "<li class=\"list-group-item justify-content-between\"> <span style=\"min-width:5%\">"
                         << it->first.getFirst() << " " << it->first.getSecond() << "</span>";
                htmlFile << "<HR style=\"height:10px; margin-left:30px; width:" << it->second
                         << "0px; max-width:80%\" COLOR=\"#03c1e3\" ALIGN=\"LEFT\">";
                htmlFile << "<span class=\"badge badge-default badge-pill\">" << it->second << "</span>" << "</li>\n";
            }
        }

        htmlFile << "</ul>";
        htmlFile << "</body></html>";
        htmlFile.close();
    }


};

#endif //CPP_BIGRAMS_CONCURRENTUNORDEREDMAP_HPP