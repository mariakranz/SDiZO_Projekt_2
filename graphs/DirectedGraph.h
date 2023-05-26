//
// Created by szef on 21.05.2023.
//

#ifndef SDIZO_PROJEKT_2_DIRECTEDGRAPH_H
#define SDIZO_PROJEKT_2_DIRECTEDGRAPH_H


#include "Graph.h"
#include <string>

class DirectedGraph : public Graph {
//    void initializeSingleSource(int *&d, int *&parents);              //pomocnicza metoda do algorytmu Dijkstry
//    void relax(int u, int v, int *&d, int *&parents);                               //pomocnicza metoda do algorytmu Dijkstry - relaksacja (oslabienie ograniczen)
//    void printPath(int startVertex, int endVertex);
public:
    DirectedGraph(int verticesNumber, int edgesNumber);
    void addEdge(int tail, int head, int cost);           //tail - wierzcholek poczatkowy, head - wierzcholek koncowy, skierowany badz nieeskierowany

    bool areAllWagesPositive();                     //dla algorytmu Dijkstry wszystkie wagi musza byc nieujemne
    setNode* DijkstraAdjMatrix(int source);
    setNode* DijkstraAdjList(int source);

    setNode* BellmanFordAdjMatrix(int source);
    setNode* BellmanFordAdjList(int source);

};


#endif //SDIZO_PROJEKT_2_DIRECTEDGRAPH_H
