//
// Created by szef on 03.05.2023.
//

#ifndef SDIZO_PROJEKT_2_FILEDATA_H
#define SDIZO_PROJEKT_2_FILEDATA_H


#include <string>
struct edge{
    int tail;       //tail -> head
    int head;
    int cost;
};

class FileData {
    int verticesNumber;
    int edgesNumber;
    int startVertex;
    int endVertex;
    //int **edges;
    edge* edgesTab;     //wskaznik na tablice struktur

public:
    FileData();
    ~FileData();

    int readDataFromFile(std::string fileName);
    int getVerticesNumber();
    int getEdgesNumber();
    int getStartVertex();
    int getEndVertex();
    edge* getEdges();
};


#endif //SDIZO_PROJEKT_2_FILEDATA_H
