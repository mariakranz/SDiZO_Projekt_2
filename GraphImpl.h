//
// Created by szef on 27.04.2023.
//

#ifndef SDIZO_PROJEKT_2_GRAPHIMPL_H
#define SDIZO_PROJEKT_2_GRAPHIMPL_H

#include <string>
//#include "LinkedList.h"

struct listNode{
    int vertex, cost;
    listNode* next;
};

struct Graph{           //lista sasiedztwa
    int verticesNumber;
    listNode** adjacencyList;
};

class GraphImpl {
    int verticesNumber;               //ilosc wierzcholkow
    int** adjacencyMatrix;       //macierz sąsiedztwa - tablica dwuwymiarowa

    listNode** tablicaList;
    listNode* lista;
    //listNode* tail;

    //LinkedList* adjacencyList;         //wskaznik na tablice list sąsiedztwa

    //node* tail;
    void insertNodeToAdjList(int vertex, int cost);
public:
    GraphImpl(int verticesNumber, int edgesNumber);        //dla MST
    GraphImpl(int verticesNumber, int edgesNumber, int startVertex);      //dla najkrotszej sciezki
    GraphImpl(int verticesNumber, int edgesNumber, int startVertex, int endVertex);

    ~GraphImpl();

    void addEdge(int tail, int head, int cost, bool directed);           //tail - wierzcholek poczatkowy, head - wierzcholek koncowy, skierowany badz nieeskierowany
    void printAdjacencyMatrix();
    void printAdjacencyList();

};


#endif //SDIZO_PROJEKT_2_GRAPHIMPL_H
