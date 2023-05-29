//
// Created by szef on 21.05.2023.
//

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

    PriorityQueue* queue = new PriorityQueue(verticesNumber, V);    //kluczami sa wartosci d (Cormen)
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

    PriorityQueue* queue = new PriorityQueue(verticesNumber, V);    //kluczami sa wartosci d (Cormen)

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

setNode* DirectedGraph::BellmanFordAdjMatrix(int source) {
    setNode* V = new setNode[verticesNumber];   //zbior wierzcholkow
    for(int i = 0; i < verticesNumber; i++){
        V[i].rank = infinity;
        V[i].parent = -1;                                            // - 1 zamiast NIL
    }
    V[source].rank = 0;
    V[source].parent = source;

    for (int i = 0; i < verticesNumber-1; i++){
        for (int u = 0; u < verticesNumber; u++){
            for (int v = 0; v < verticesNumber; v++){
                if(adjacencyMatrix[u][v] != infinity) {
                    if (V[v].rank > V[u].rank + adjacencyMatrix[u][v] &&
                        !(adjacencyMatrix[u][v] < 0 && V[u].rank < INT_MIN - adjacencyMatrix[u][v]) &&  //sprawdzanie czy nie wystapi przepelnienie integera
                        !(adjacencyMatrix[u][v] > 0 && V[u].rank > INT_MAX - adjacencyMatrix[u][v]) ) {
                        V[v].rank = V[u].rank + adjacencyMatrix[u][v];
                        V[v].parent = u;
                    }
                }
            }
        }
    }

    for (int u = 0; u < verticesNumber; u++){
        for (int v = 0; v < verticesNumber; v++){
            if(adjacencyMatrix[u][v] != infinity) {
                if (V[v].rank > V[u].rank + adjacencyMatrix[u][v] &&
                    !(adjacencyMatrix[u][v] < 0 && V[u].rank < INT_MIN - adjacencyMatrix[u][v]) &&
                    !(adjacencyMatrix[u][v] > 0 && V[u].rank > INT_MAX - adjacencyMatrix[u][v])) {
                    if (V[v].rank > V[u].rank + adjacencyMatrix[u][v]) return nullptr;        //w Cormienie return false - jest ujemny cykl w grafie
                }
            }
        }
    }

    return V; //return true - nie ma ujemnego cyklu w grafie
}

setNode *DirectedGraph::BellmanFordAdjList(int source) {
    setNode* V = new setNode[verticesNumber];   //zbior wierzcholkow
    for(int i = 0; i < verticesNumber; i++){
        V[i].rank = infinity;
        V[i].parent = -1;                                            // - 1 zamiast NIL
    }
    V[source].rank = 0;
    V[source].parent = source;

    for (int i = 0; i < verticesNumber-1; i++){
        for (int u = 0; u < verticesNumber; u++){
            listNode* v = adjacencyList[u];
            while(v) {
                if(V[v->vertex].rank > V[u].rank + v->cost &&
                    !(v->cost < 0 && V[u].rank < INT_MIN - v->cost) &&
                    !(v->cost > 0 && V[u].rank > INT_MAX - v->cost)){
                    V[v->vertex].rank = V[u].rank + v->cost;
                    V[v->vertex].parent = u;
                }
                v = v->next;
            }
        }
    }

    for (int u = 0; u < verticesNumber; u++){
        listNode* v = adjacencyList[u];
        while(v) {
            if(V[v->vertex].rank > V[u].rank + v->cost &&
               !(v->cost < 0 && V[u].rank < INT_MIN - v->cost) &&
               !(v->cost > 0 && V[u].rank > INT_MAX - v->cost)){
                if (V[v->vertex].rank > V[u].rank + v->cost) return nullptr;
            }
            v = v->next;
        }
    }

    return V; //return true - nie ma ujemnego cyklu w grafie
}
