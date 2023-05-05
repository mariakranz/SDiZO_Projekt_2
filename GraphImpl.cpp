//
// Created by szef on 27.04.2023.
//

#include <iostream>
#include "GraphImpl.h"
#include "PriorityQueue.h"

GraphImpl::GraphImpl(int verticesNumber, int edgesNumber) {        //dla MST - krawedzie nieskierowane!!
    this->verticesNumber = verticesNumber;
    this->edgesNumber = edgesNumber;

    adjacencyMatrix = new int * [verticesNumber];                 //tworzenie macierzy sasiedztwa o odpowiednim rozmiarze
    for (int i = 0; i < verticesNumber; i++) {
        adjacencyMatrix[i] = new int [verticesNumber];
        for (int j = 0; j < verticesNumber; j++){
            //adjacencyMatrix[i][j] = std::numeric_limits<int>::infinity();     //dla int funkcja infinity zwraca 0
            //adjacencyMatrix[i][j] = std::numeric_limits<int>::max();
            adjacencyMatrix[i][j] = INT_MAX;                //ustaw domyslnie wszedzie brak polaczen
        }
    }

    listTable = new listNode * [verticesNumber];      //tworzenie tablicy list sąsiedztwa (tablica wskaznikow na strukture listNode)
    for(int i = 0; i < verticesNumber; i++ ) {
        listTable [i] = nullptr;
    }

    MSTtab = nullptr;
}

GraphImpl::~GraphImpl() {

}

void GraphImpl::addEdge(int tail, int head, int cost, bool directed) {

    adjacencyMatrix[tail][head] = cost;     //dodawanie do macierzy sasiedztwa

    listNode* newNode = new listNode{head, cost, listTable[tail]};
    listTable[tail] = newNode;

    if (!directed && tail != head){         //jesli wierzcholek ma krawedz z samym soba to nie tworz kolejnego wierzcholka (szczegolnie bylo by to widoczne w liscie sasiedztwa bo wartosc bylaby zduplikowana)
        adjacencyMatrix[head][tail] = cost;
        listNode *nextNewNode = new listNode{tail, cost, listTable[head]};
        listTable[head] = nextNewNode;

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
        listNode* node = listTable[i];
        while(node)
        {
            std::cout << "->";
            std::cout << node->vertex << ":" << node->cost;
            node = node->next;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void GraphImpl::MSTKruskalAdjMatrix() {
    MSTtab = new MSTNode [verticesNumber-1];        //kazde drzewo rozpinajace ma dokladnie |V|-1 krawedzi
    int elem = 0;


    Set* set = new Set(verticesNumber);
    for (int i = 0; i < verticesNumber; i++) set->makeSet(i);       //dla kazdego wierzcholka tworzony jest set (z tym jednym wierzcholkiem)
    PriorityQueue* queue = new PriorityQueue(edgesNumber,verticesNumber,adjacencyMatrix);
//    queue->printHeap();
    for (int i = 0; i < edgesNumber; i++){
        queueElement edge = queue->extractMin();
//        queue->printHeap();
//        std::cout << "edge->tail: " << edge.tail << std::endl;
//        set->printSetsTable();
        if (set->findSet(edge.tail) != set->findSet(edge.head)) {
//            std::cout << "Tu3\n";
            set->unionSets(edge.tail, edge.head);
            //std::cout << "(" <<  edge.tail << ", " << edge.head << ")    " << edge.cost << std::endl;

            MSTtab[elem].tail = edge.tail;
            MSTtab[elem].head = edge.head;
            MSTtab[elem].cost = edge.cost;
            elem++;
        }
    }
}

void GraphImpl::MSTKruskalAdjList() {
    MSTtab = new MSTNode [verticesNumber-1];        //kazde drzewo rozpinajace ma dokladnie |V|-1 krawedzi
    int elem = 0;

    Set* set = new Set(verticesNumber);
    for (int i = 0; i < verticesNumber; i++) set->makeSet(i);       //dla kazdego wierzcholka tworzony jest set (z tym jednym wierzcholkiem)
    PriorityQueue* queue = new PriorityQueue(edgesNumber, verticesNumber, listTable);
    for (int i = 0; i < edgesNumber; i++){
        queueElement edge = queue->extractMin();
        if (set->findSet(edge.tail) != set->findSet(edge.head)) {
            set->unionSets(edge.tail, edge.head);

            MSTtab[elem].tail = edge.tail;
            MSTtab[elem].head = edge.head;
            MSTtab[elem].cost = edge.cost;
            elem++;
        }
    }

}

void GraphImpl::printMST() {
    std::cout << "MST: " << std::endl;
    std::cout << "Edge:   Weight:" << std::endl;
    if (!MSTtab) return;                            //jesli MST nie zostalo utorzone
    for (int i = 0; i < verticesNumber-1; i++) {
        MSTNode edge = MSTtab[i];
        std::cout << "(" <<  edge.tail << ", " << edge.head << ")    " << edge.cost << std::endl;
    }
    std::cout << "MST = " << sumMST() << std::endl;
}

int GraphImpl::sumMST() {
    if (!MSTtab) return {};
    int sum = 0;
    for (int i = 0; i < verticesNumber - 1; i++) {
        sum+=MSTtab[i].cost;
    }
    return sum;
}




Set::Set(int verticesNumber) {
    size = verticesNumber;
    setsTable = new setNode [size];
}

Set::~Set() {
    delete [] setsTable;
}

void Set::makeSet(int x) {
    setsTable[x].parent = x;        //poczatkowy wierzcholek jest korzeniem (i reprezentantem wlasnego setu)
    setsTable[x].rank = 0;
}

void Set::unionSets(int x, int y) {
    link(findSet(x), findSet(y));
}

void Set::link(int x, int y) {
    if (setsTable[x].rank > setsTable[y].rank) setsTable[y].parent = x;
    else{
        setsTable[x].parent = y;
        if (setsTable[x].rank == setsTable[y].rank) setsTable[y].rank++;
    }
}

int Set::findSet(int x) {
    if (x != setsTable[x].parent) setsTable[x].parent = findSet(setsTable[x].parent);
    return setsTable[x].parent;
}

void Set::printSetsTable() {
    std::cout << "Tablica setow:\n";
    for (int i = 0; i < size; i++){
        std::cout << i << ", p: " << setsTable[i].parent << ", rank: " << setsTable[i].rank << std::endl;
    }

}


