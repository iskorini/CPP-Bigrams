//
// Created by iskor on 28/02/2017.
//

#include <unordered_map>
#include <fstream>
#include <mutex>

#ifndef CPP_BIGRAMS_CONCURRENTUNORDEREDMAP_HPP
#define CPP_BIGRAMS_CONCURRENTUNORDEREDMAP_HPP

#endif //CPP_BIGRAMS_CONCURRENTUNORDEREDMAP_HPP

template<typename type>
class ConcurrentUnorderedIntMap {
private:
    std::unordered_map<type, int> unorderedMap;
    std::mutex mutex;
public:
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
    void writeHtmlFile(std::string path) {
        std::ofstream htmlFile;
        htmlFile.open(path);
        htmlFile << "<!DOCTYPE html><html><head></head>";
        htmlFile
                << "<link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0-alpha.6/css/bootstrap.min.css\" integrity=\"sha384-rwoIResjU2yc3z8GV/NPeZWAv56rSmLldC3R/AZzGRnGxQQKnKkoFVhFQhNUwEyJ\" crossorigin=\"anonymous\">";
        htmlFile << "<body>";
        htmlFile << "<h1>Bigrams</h1>";
        htmlFile << "<ul class=\"col-sm-12 list-group\">\n";

        for (auto it = unorderedMap.begin(); it != unorderedMap.end(); ++it) {
            htmlFile << "<li class=\"list-group-item justify-content-between\"> <span style=\"min-width:5%\">"
                     << it->first << "</span>";
            htmlFile << "<HR style=\"height:10px; margin-left:30px; width:" << it->second
                     << "0px; max-width:80%\" COLOR=\"#03c1e3\" ALIGN=\"LEFT\">";
            htmlFile << "<span class=\"badge badge-default badge-pill\">" << it->second << "</span>" << "</li>\n";
        }
        htmlFile << "</ul>";
        htmlFile << "</body></html>";
        htmlFile.close();
    }

};