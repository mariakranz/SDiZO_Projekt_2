//
// Created by szef on 21.05.2023.
//

#ifndef SDIZO_PROJEKT_2_UNDIRECTEDGRAPH_H
#define SDIZO_PROJEKT_2_UNDIRECTEDGRAPH_H


#include "Graph.h"


#include <string>

enum color{WHITE, GREY, BLACK};                                     //do DFS

class UndirectedGraph : public Graph {

    void DFSVisit(int u, color *&colors, int *&parents, int time);

public:
    UndirectedGraph(int verticesNumber, int edgesNumber);           //dla MST

    void addEdge(int tail, int head, int cost);                     //tail - wierzcholek poczatkowy, head - wierzcholek koncowy

    int DFS();
    bool isConnected();                                             //czy graf jest spojny

    MSTEdge* MSTKruskalAdjMatrix();
    MSTEdge* MSTKruskalAdjList();
    MSTEdge* MSTPrimAdjMatrix(int r);                               //r - wierzcholek od ktorego zaczynamy wyznaczanie drzewa
    MSTEdge* MSTPrimAdjList(int r);

    void sortMSTTab(int p, int r);                                  //quicksort po peirwszym wierzcholku

};


#endif //SDIZO_PROJEKT_2_UNDIRECTEDGRAPH_H
