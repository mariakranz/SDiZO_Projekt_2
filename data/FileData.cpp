//
// Created by szef on 03.05.2023.
//

#include <fstream>
#include <iostream>
#include "FileData.h"

FileData::FileData() {
    verticesNumber = edgesNumber = startVertex = endVertex = 0;
    //edges = nullptr;
    edgesTab = nullptr;
}

FileData::~FileData() {
    verticesNumber = edgesNumber = startVertex = endVertex = 0;         //idk czy to ma sens
}

int FileData::getVerticesNumber() {
    return verticesNumber;
}

int FileData::getEdgesNumber() {
    return edgesNumber;
}

int FileData::getStartVertex() {
    return startVertex;
}

int FileData::getEndVertex() {
    return endVertex;
}

int FileData::readDataFromFile(std::string filePath) {
    std::fstream file;
    file.open(filePath, std::ios::in);
    if(file.is_open()) {
        file >> edgesNumber;
        file >> verticesNumber;
        file >> startVertex;
        file >> endVertex;
        if (file.fail()) {
            //cout << "File error - READ SIZE" << stendl;
            file.close();
            return -1;
        }

        edgesTab = new edge [edgesNumber];
        for (int i = 0; i < edgesNumber; i++) {
            file >> edgesTab[i].tail;     //wierzcholek poczatkowy
            file >> edgesTab[i].head;     //wierzcholek koncowy
            file >> edgesTab[i].cost;     //waga

            if(file.fail())
            {
                //cout << "File error - READ DATA" << endl;
                delete [] edgesTab;
                //delete edgesTab;
                file.close();
                return -1;
            }
        }

        file.close();
        return 0;
    }
    else
        //cout << "File error - OPEN" << endl;
    return -1;
}

edge* FileData::getEdges() {
    return edgesTab;
}


