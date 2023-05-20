//
// Created by szef on 05.05.2023.
//

#ifndef SDIZO_PROJEKT_2_PRIORITYQUEUE_H
#define SDIZO_PROJEKT_2_PRIORITYQUEUE_H

#include "GraphImpl.h"
#include "Set.h"

class PriorityQueue {           //implementacja na bazie kopca
    int size;
//    queueElement* heapTable;        //wskaznik na tablice (kopiec) elementow queueElement
    MSTEdge* heapTable;
    Set* verticesTable;
    void buildMinHeap();                   //zbuduj kopiec minimalny (wedlug wag)
//    void heapify(int index);
    int parent(int);                    //zwraca numer indeksu rodzica
    int left(int);                      //zwraca numer indeksu lewego syna
    int right(int);
public:
    PriorityQueue(int size);
    PriorityQueue(int edgesNumber, int verticesNumber, int** adjacencyMatrix);
    PriorityQueue(int edgesNumber, int verticesNumber, listNode** listTable);
//    PriorityQueue(int verticesNumber, Set* vertices);       //kolejka wierzchołków
    PriorityQueue(int verticesNumber, setNode* vertices);   //liczba wierzcholkow, tablica wierzcholkow
    ~PriorityQueue();

    void addEdge(int tail, int head, int cost);
//    queueElement extractMin();
    MSTEdge extractMin();
    void heapify(int index);
    void printHeap();
    bool isEmpty();
    int thisVerticleisInQueue(int v);
    int updateKey(int vertex, int key);
    int updateValues(int vertex, int key, int parent);
    int vertexKeyValue(int vertex);
};


#endif //SDIZO_PROJEKT_2_PRIORITYQUEUE_H
