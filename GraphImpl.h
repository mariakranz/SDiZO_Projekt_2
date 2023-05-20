//
// Created by szef on 27.04.2023.
//

#ifndef SDIZO_PROJEKT_2_GRAPHIMPL_H
#define SDIZO_PROJEKT_2_GRAPHIMPL_H

#include <string>

struct MSTEdge{             //krawedzie drzewa
    int tail, head, cost;
};

//struct vertex{     //do algorytmu Prima
//    int u, key, parent;
//};

struct setNode{             //do klasy Set i PriorityQueue
    int rank, parent;
};

struct listNode{          //element listy sąsiedztwa
    int vertex, cost;
    listNode* next;
};

class GraphImpl {
    bool directed;
    int verticesNumber;               //ilosc wierzcholkow
    int edgesNumber;

    int** adjacencyMatrix;       //macierz sąsiedztwa - tablica dwuwymiarow
    listNode** adjacencyList;     //lista sąsiedztwa - tablica list (tablica wskaznikow na struktury)

    MSTEdge* MSTtab;            //tablica z krawedziami drzewa
    int sumMST;                 //suma wag krawedzi drzewa
public:
    GraphImpl(int verticesNumber, int edgesNumber);        //dla MST
    GraphImpl(int verticesNumber, int edgesNumber, int startVertex);      //dla najkrotszej sciezki
    GraphImpl(int verticesNumber, int edgesNumber, int startVertex, int endVertex);

    ~GraphImpl();

    void addEdge(int tail, int head, int cost);           //tail - wierzcholek poczatkowy, head - wierzcholek koncowy, skierowany badz nieeskierowany
    void printAdjacencyMatrix();
    void printAdjacencyList();

    void DFS();
    bool isConnected();

    void MSTKruskalAdjMatrix();
    void MSTKruskalAdjList();
    void MSTPrimAdjMatrix(int r);               //r - wierzcholek od ktorego zaczynamy wyznaczanie drzewa
    void MSTPrimAdjList(int r);
    void printMST();
    void sortMSTTab(int p, int r);              //quicksort po peirwszym wierzcholku
};


#endif //SDIZO_PROJEKT_2_GRAPHIMPL_H
