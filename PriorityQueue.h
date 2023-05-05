//
// Created by szef on 05.05.2023.
//

#ifndef SDIZO_PROJEKT_2_PRIORITYQUEUE_H
#define SDIZO_PROJEKT_2_PRIORITYQUEUE_H

#include "GraphImpl.h"

struct queueElement{
    int head, tail, cost;
};

class PriorityQueue {           //implementacja na bazie kopca
    int size;
    queueElement* heapTable;        //wskaznik na tablice (kopiec) elementow queueElement
    void buildMinHeap();                   //zbuduj kopiec minimalny (wedlug wag)
    void heapify(int index);
    int parent(int);                    //zwraca numer indeksu rodzica
    int left(int);                      //zwraca numer indeksu lewego syna
    int right(int);
public:
    PriorityQueue(int size);
    PriorityQueue(int edgesNumber, int verticesNumber, int** adjacencyMatrix);
    PriorityQueue(int edgesNumber, int verticesNumber, listNode** listTable);
    ~PriorityQueue();

    void addEdge(int tail, int head, int cost);
    queueElement extractMin();
    void printHeap();
};


#endif //SDIZO_PROJEKT_2_PRIORITYQUEUE_H
