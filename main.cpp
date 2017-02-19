
#include <iostream>
#include <string>
#include <queue>
#include "ctpl.h"
#include "boost/lockfree/queue.hpp"
//#include "boost/filesystem.hpp"
#include <boost/foreach.hpp>
#include <dirent.h>
#include "Producer.h"
#include "Consumer.h"


using namespace std;

bool has_suffix(const std::string &str, const std::string &suffix)
{
    return str.size() >= suffix.size() &&
           str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}





void readTXTFileFromDirectory(char *path, boost::lockfree::queue<string *> &fileQueue ) {
    DIR *dir;
    struct dirent *ent;
    cout << "STAMPA DI INSERIMENTO" << endl;
    if ((dir = opendir (path)) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            string fileName = ent->d_name;
            if (has_suffix(fileName, ".txt")) {
                fileQueue.push(&fileName);
                cout << fileName << endl;
            }
        }
        closedir (dir);
    } else {
        perror ("");
    }


    string merda = "merdaculo";
    fileQueue.push(&merda);

    cout << "STAMPE DI POP" << endl;
    while (!fileQueue.empty()) {
        string *element;
        fileQueue.pop(element);
        cout << *element << endl;
    }



}





int main(int argc, char **argv) {
    std::atomic_int fileQueueSize = 0;
    std::atomic_int qSize = 0;
    ctpl::thread_pool p(8);
    /*
     *
     */
    fileQueueSize++;
    fileQueueSize++;
    /*
     *
     */
    boost::lockfree::queue<std::string*> fileQueue(999);
    string file1 = "pqorwgoprgqopig rg regi reg ew g rg kggr  rwe eergprgjergu er iogewruiogew rjgewrjoiguwe rgoiwue rgioe urgjioweu gjoiweug "
            "erguerwjgew9jgr ewrgj ewrg9jwe rgweur gjrwe gwre9gjrewg erwjgjeuj ewrgerjwp gjwerg"
            "gweiorgerwinugeirgnwe grewrigrnegiuwe nrgweirg w"
            "thttr"
            "trh"
            "hrt"
            "ehret"
            "rher"
            "ty"
            "j rt "
            "eryy"
            "y "
            "jye "
            " jy yejy jeryh tr ht"
            "r tye"
            " yj"
            " yet"
            " ty"
            " e"
            " tr"
            "wqdf";
    string file2 = "oirqwugniqr g rgrjgeju erwgerw eg jgre jgjoirgewoji grerewjo ergjeoipgjreoj gerj greojwgj ergjoergj oer jge rwogoij reoji gr joipgew"
            "erg"
            "th"
            "r"
            "yj"
            "yjyje rrt tr  ute  tueturu etr ue uetu  uteu t et uuet ue ueu srgs gn sni  sadfiuasj fwijuerj ueiu";
    fileQueue.push(&file1);
    fileQueue.push(&file2);
    boost::lockfree::queue<std::string*> q(999);
    //readTXTFileFromDirectory("C:\\Users\\iskor\\CLionProjects\\CPP-Bigrams\\File", fileQueue);
    Producer producer1("culo", q, fileQueue, &fileQueueSize, &qSize);
    Producer producer2("blodo", q, fileQueue, &fileQueueSize, &qSize);
    Consumer consumer(q, &fileQueueSize, &qSize);
    p.push(std::ref(producer1));
    return 0;
}
