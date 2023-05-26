//
// Created by szef on 21.05.2023.
//

#include <climits>
#include "Graph.h"


Graph::Graph(int verticesNumber, int edgesNumber) {
    adjacencyMatrix = new int * [verticesNumber];                 //tworzenie macierzy sasiedztwa o odpowiednim rozmiarze
    for (int i = 0; i < verticesNumber; i++) {
        adjacencyMatrix[i] = new int [verticesNumber];
        for (int j = 0; j < verticesNumber; j++){
            adjacencyMatrix[i][j] = infinity;               //ustaw domyslnie wszedzie brak polaczen
        }
    }

    adjacencyList = new listNode * [verticesNumber];      //tworzenie tablicy list sąsiedztwa (tablica wskaznikow na strukture listNode)
    for(int i = 0; i < verticesNumber; i++ ) {
        adjacencyList [i] = nullptr;
    }
}

Graph::~Graph() {
    if (adjacencyMatrix != nullptr) {
        for (int i = 0; i < verticesNumber; i++) {
            delete[] adjacencyMatrix[i];
        }
        delete[] adjacencyMatrix;
    }

    if (adjacencyList != nullptr) {
        for (int i = 0; i < verticesNumber; i++) {
            listNode *node = adjacencyList[i];
            while (node) {
                listNode *tmpNode = node;
                node = node->next;
                delete tmpNode;
            }
        }
        delete[] adjacencyList;
    }
}

int **Graph::getAdjMatrix() {
    return adjacencyMatrix;
}

listNode **Graph::getAdjList() {
    return adjacencyList;
}

int Graph::getVeritcesNunber() {
    return verticesNumber;
}


