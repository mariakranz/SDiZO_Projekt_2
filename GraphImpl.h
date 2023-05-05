//
// Created by szef on 27.04.2023.
//

#ifndef SDIZO_PROJEKT_2_GRAPHIMPL_H
#define SDIZO_PROJEKT_2_GRAPHIMPL_H

#include <string>

struct setNode{
    int rank, parent;
};

class Set{
    setNode* setsTable;                 //tablica setow czyli drzew
    int size;
    void link(int x, int y);
public:
    Set(int verticesNumber);
    ~Set();
    void makeSet(int x);
    void unionSets(int x, int y);
    int findSet(int x);

    void printSetsTable();              //funkcja pomocnicza - wyswietlanie setow

};

struct MSTNode{
    int tail, head, cost;
};


struct listNode{
    int vertex, cost;
    listNode* next;
};

//struct Graph{           //lista sasiedztwa
//    int verticesNumber;
//    listNode** adjacencyList;
//};

class GraphImpl {
    int verticesNumber;               //ilosc wierzcholkow
    int edgesNumber;
    int** adjacencyMatrix;       //macierz sąsiedztwa - tablica dwuwymiarowa

    listNode** adjacencyList;     //lista sąsiedztwa - tablica list (tablica wskaznikow na struktury)

    MSTNode* MSTtab;
    int sumMST();
public:
    GraphImpl(int verticesNumber, int edgesNumber);        //dla MST
    GraphImpl(int verticesNumber, int edgesNumber, int startVertex);      //dla najkrotszej sciezki
    GraphImpl(int verticesNumber, int edgesNumber, int startVertex, int endVertex);

    ~GraphImpl();

    void addEdge(int tail, int head, int cost, bool directed);           //tail - wierzcholek poczatkowy, head - wierzcholek koncowy, skierowany badz nieeskierowany
    void printAdjacencyMatrix();
    void printAdjacencyList();

    void MSTKruskalAdjMatrix();
    void MSTKruskalAdjList();
    void printMST();
    void sortMSTTab(int p, int r);              //quicksort po peirwszym wierzcholku

};


#endif //SDIZO_PROJEKT_2_GRAPHIMPL_H
