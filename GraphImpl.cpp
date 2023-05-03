//
// Created by szef on 27.04.2023.
//

#include <iostream>
#include <limits>
#include "GraphImpl.h"

GraphImpl::GraphImpl(int verticesNumber, int edgesNumber) {        //dla MST - krawedzie nieskierowane!!
    this->verticesNumber = verticesNumber;

    adjacencyMatrix = new int * [verticesNumber];                 //tworzenie macierzy sasiedztwa o odpowiednim rozmiarze
    for (int i = 0; i < verticesNumber; i++) {
        adjacencyMatrix[i] = new int [verticesNumber];
        for (int j = 0; j < verticesNumber; j++){
            //adjacencyMatrix[i][j] = std::numeric_limits<int>::infinity();     //dla int funkcja infinity zwraca 0
            //adjacencyMatrix[i][j] = std::numeric_limits<int>::max();
            adjacencyMatrix[i][j] = INT_MAX;                //ustaw domyslnie wszedzie brak polaczen
        }
    }

    tablicaList = new listNode * [verticesNumber];      //tworzenie tablicy list sąsiedztwa (tablica wskaznikow na strukture listNode)
    for(int i = 0; i < verticesNumber; i++ ) {
        tablicaList [ i ] = nullptr;
    }
    //tail = nullptr;

    //Graph graph = new adjen

    //adjacencyList = new node * [verticesNumber];            //tworzenie tablicy wskaznikow na listy sasiedztwa
//    adjacencyList = new LinkedList [verticesNumber];
//    for (int i = 0; i < verticesNumber; i++){
//        adjacencyList[i].
//    }
}


void GraphImpl::insertNodeToAdjList(int vertex, int cost) {
    listNode* newNode = new listNode{vertex, cost, nullptr};
//    if (tail != nullptr) tail->next = newNode;
//    tail = newNode;
}

void GraphImpl::addEdge(int tail, int head, int cost, bool directed) {

    adjacencyMatrix[tail][head] = cost;     //dodawanie do macierzy sasiedztwa


    //adjacencyList[tail]->insertTail(head, cost);  //dodawanie do listy sasiedztwa
    //listNode elem = tablicaList[tail];


//    for(int i = 0; i < verticesNumber; i++ )
//    {
//        //cin >> v1 >> v2;    // Wierzchołek startowy i końcowy krawędzi
//        listNode * p = new listNode{head, cost, tablicaList[i]};    // Tworzymy nowy element
//        //p->v = v2;          // Numerujemy go jako v2
//       //p->next = A [ v1 ]; // Dodajemy go na początek listy A [ v1 ]
//        tablicaList [ i ] = p;
//    }

    listNode* newNode = new listNode{head, cost, tablicaList[tail]};
    tablicaList[tail] = newNode;

    if (!directed){
        adjacencyMatrix[head][tail] = cost;
        //adjacencyList[head]->insertTail(tail, cost);
    }
}

void GraphImpl::printAdjacencyMatrix() {
    std::cout << "Macierz sasiedztwa:" << std::endl;
    std::cout << "     ";
    for (int i = 0; i < verticesNumber; i++){
        std::cout.width(5);
        std::cout << i;
    }
    std::cout << std::endl;

    for (int i = 0; i < verticesNumber; i++) {
        std::cout.width(5);
        std::cout << i;
        for (int j = 0; j < verticesNumber; j++){
            std::cout.width(5);
            int cost = adjacencyMatrix[i][j];
            if (cost == INT_MAX) std::cout << "-";
            else std::cout << cost;
        }
        std::cout << std::endl;
    }
}

void GraphImpl::printAdjacencyList() {
    std::cout << "Lista sasiedztwa:" << std::endl;
    for(int i = 0; i < verticesNumber; i++ )
    {
        std::cout << i;
        listNode* p = tablicaList[i];
        while( p )
        {
            std::cout << "->";
            //std::cout.width(5);
            std::cout << p->vertex << ":" << p->cost;
            p = p->next;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

