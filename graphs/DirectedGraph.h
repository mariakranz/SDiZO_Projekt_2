//
// Created by szef on 21.05.2023.
//

#ifndef SDIZO_PROJEKT_2_DIRECTEDGRAPH_H
#define SDIZO_PROJEKT_2_DIRECTEDGRAPH_H


#include "Graph.h"
#include <string>

class DirectedGraph : public Graph {
public:
    DirectedGraph(int verticesNumber, int edgesNumber);
    void addEdge(int tail, int head, int cost);           //tail - wierzcholek poczatkowy, head - wierzcholek koncowy
    bool changeAlreadyDefinedEdge(int tail, int head, int cost);

    bool areAllWagesPositive();                     //dla algorytmu Dijkstry wszystkie wagi musza byc nieujemne
    setNode* DijkstraAdjMatrix(int source);
    setNode* DijkstraAdjList(int source);

    bool isNegativeCycleMatrix(setNode* V);         //wystarczylaby jedna metoda (dla jednej reprezentacji)
    bool isNegativeCycleList(setNode* V);
    setNode* BellmanFordAdjMatrix(int source);
    setNode* BellmanFordAdjList(int source);

};


#endif //SDIZO_PROJEKT_2_DIRECTEDGRAPH_H
