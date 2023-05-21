//
// Created by szef on 21.05.2023.
//

#include <iostream>
#include "DirectedGraph.h"
#include "../structures/PriorityQueue.h"

DirectedGraph::DirectedGraph(int verticesNumber, int edgesNumber) : Graph(verticesNumber, edgesNumber){
    this->verticesNumber = verticesNumber;
    this->edgesNumber = edgesNumber;
}

void DirectedGraph::addEdge(int tail, int head, int cost) {
    adjacencyMatrix[tail][head] = cost;     //dodawanie do macierzy sasiedztwa

    listNode* newNode = new listNode{head, cost, adjacencyList[tail]};
    adjacencyList[tail] = newNode;
}

setNode *DirectedGraph::DijkstraAdjMatrix(int source) {
    if (source < 0 or source > verticesNumber-1) return nullptr;
    setNode* V = new setNode[verticesNumber];   //zbior wierzcholkow
    for(int i = 0; i < verticesNumber; i++){
        V[i].rank = infinity;
        V[i].parent = -1;                                            // - 1 zamiast NIL
    }
    V[source].rank = 0;
    V[source].parent = source;

    PriorityQueue* queue = new PriorityQueue(verticesNumber, V);    //kluczami sa wartosci d
    while (!queue->isEmpty()){
        MSTEdge u = queue->extractMin();
        for (int v = 0; v < verticesNumber; v++){
            if(adjacencyMatrix[u.head][v] != infinity) {
                if(V[v].rank > V[u.head].rank + adjacencyMatrix[u.head][v] && V[u.head].rank + adjacencyMatrix[u.head][v] > 0){     //drugi waruenk dla przypadkow gdy nie suma > INT_MAX, bo wtedy będzie przekroczenie zakresu i zacznie zliczac od maksymalnej liczby ujemnej
                    V[v].rank = V[u.head].rank + adjacencyMatrix[u.head][v];
                    V[v].parent = u.head;
                    queue->updateValues(v, V[v].rank, V[v].parent);
                }
            }
        }
        std::cout << "Tablica wierzcholkow:" << std::endl;
        for(int i = 0; i < verticesNumber; i++){
            std::cout << i << ": " << V[i].parent << " - " << V[i].rank << std::endl;
        }
    }
    return V;
}

setNode *DirectedGraph::DijkstraAdjList(int source) {
    if (source < 0 or source > verticesNumber-1) return nullptr;
    setNode* V = new setNode[verticesNumber];   //zbior wierzcholkow
    for(int i = 0; i < verticesNumber; i++){
        V[i].rank = infinity;
        V[i].parent = -1;                                            // - 1 zamiast NIL
    }
    V[source].rank = 0;
    V[source].parent = source;

    PriorityQueue* queue = new PriorityQueue(verticesNumber, V);    //kluczami sa wartosci d

    while (!queue->isEmpty()){
        MSTEdge u = queue->extractMin();

        listNode* v = adjacencyList[u.head];
        while(v) {
            if(V[v->vertex].rank > V[u.head].rank + v->cost && V[u.head].rank + v->cost > 0){
                V[v->vertex].rank = V[u.head].rank + v->cost;
                V[v->vertex].parent = u.head;
                queue->updateValues(v->vertex, V[v->vertex].rank, V[v->vertex].parent);
            }
            v = v->next;
        }
    }

    return V;
}

bool DirectedGraph::areAllWagesPositive() {

    for(int i = 0; i < verticesNumber; i++){
        listNode *node = adjacencyList[i];
        while (node) {
            if (node->cost < 0) return false;
            node = node->next;
        }
    }
    return true;
}
