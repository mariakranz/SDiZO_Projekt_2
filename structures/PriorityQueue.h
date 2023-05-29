//
// Created by szef on 05.05.2023.
//

#ifndef SDIZO_PROJEKT_2_PRIORITYQUEUE_H
#define SDIZO_PROJEKT_2_PRIORITYQUEUE_H


#include "Set.h"
#include "../graphs/Graph.h"

class PriorityQueue {                                                           //implementacja na bazie kopca
    int size;
    MSTEdge* heapTable;
    void buildMinHeap();                                                        //zbuduj kopiec minimalny (wedlug wag)
    int parent(int);                                                            //zwraca numer indeksu rodzica
    int left(int);                                                              //zwraca numer indeksu lewego syna
    int right(int);
public:
    PriorityQueue(int edgesNumber, int verticesNumber, int** adjacencyMatrix);
    PriorityQueue(int edgesNumber, int verticesNumber, listNode** listTable);
    PriorityQueue(int verticesNumber, setNode* vertices);                       //kolejka wierzcholkow
    ~PriorityQueue();

    MSTEdge extractMin();
    void heapify(int index);
    void printHeap();
    bool isEmpty();
    int thisVertexIsInQueue(int v);
    int updateValues(int vertex, int key, int parent);
};


#endif //SDIZO_PROJEKT_2_PRIORITYQUEUE_H
