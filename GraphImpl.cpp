//
// Created by szef on 27.04.2023.
//

#include <iostream>
#include "GraphImpl.h"
#include "PriorityQueue.h"
#include "Set.h"

GraphImpl::GraphImpl(int verticesNumber, int edgesNumber) {        //dla MST - krawedzie nieskierowane!!
    directed = false;
    this->verticesNumber = verticesNumber;
    this->edgesNumber = edgesNumber;

    adjacencyMatrix = new int * [verticesNumber];                 //tworzenie macierzy sasiedztwa o odpowiednim rozmiarze
    for (int i = 0; i < verticesNumber; i++) {
        adjacencyMatrix[i] = new int [verticesNumber];
        for (int j = 0; j < verticesNumber; j++){
            adjacencyMatrix[i][j] = INT_MAX;                //ustaw domyslnie wszedzie brak polaczen
        }
    }

    adjacencyList = new listNode * [verticesNumber];      //tworzenie tablicy list sąsiedztwa (tablica wskaznikow na strukture listNode)
    for(int i = 0; i < verticesNumber; i++ ) {
        adjacencyList [i] = nullptr;
    }

    MSTtab = nullptr;
    sumMST = 0;
}

GraphImpl::~GraphImpl() {
    for (int i = 0; i < verticesNumber; i++) {
        delete [] adjacencyMatrix[i];
    }
    delete [] adjacencyMatrix;

    for (int i = 0; i < verticesNumber; i++){
        listNode* node = adjacencyList[i];
        while(node){
            listNode* tmpNode = node;
            node = node->next;
            delete tmpNode;
        }
    }

    delete [] adjacencyList;
    delete [] MSTtab;
}

void GraphImpl::addEdge(int tail, int head, int cost) {

    adjacencyMatrix[tail][head] = cost;     //dodawanie do macierzy sasiedztwa

    listNode* newNode = new listNode{head, cost, adjacencyList[tail]};
    adjacencyList[tail] = newNode;

    if (!directed && tail != head){         //jesli wierzcholek ma krawedz z samym soba to nie tworz kolejnego wierzcholka (szczegolnie bylo by to widoczne w liscie sasiedztwa bo wartosc bylaby zduplikowana)
        adjacencyMatrix[head][tail] = cost;
        listNode *nextNewNode = new listNode{tail, cost, adjacencyList[head]};
        adjacencyList[head] = nextNewNode;

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
        listNode* node = adjacencyList[i];
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
    if (MSTtab) delete [] MSTtab;                   //pomyslec czy nie zrobic klasy MST z dekonstruktoerm zeby sam usuwal
    sumMST = 0;
    MSTtab = new MSTEdge [verticesNumber - 1];        //kazde drzewo rozpinajace ma dokladnie |V|-1 krawedzi
    int elem = 0;


    Set* set = new Set(verticesNumber);
    for (int i = 0; i < verticesNumber; i++) set->makeSet(i);       //dla kazdego wierzcholka tworzony jest set (z tym jednym wierzcholkiem)
    PriorityQueue* queue = new PriorityQueue(edgesNumber,verticesNumber,adjacencyMatrix);
    for (int i = 0; i < edgesNumber; i++){
//        queueElement edge = queue->extractMin();
        MSTEdge edge = queue->extractMin();
        if (set->findSet(edge.tail) != set->findSet(edge.head)) {
            set->unionSets(edge.tail, edge.head);

//            MSTtab[elem].tail = edge.tail;
//            MSTtab[elem].head = edge.head;
//            MSTtab[elem].cost = edge.cost;
            MSTtab[elem] = edge;
            elem++;
            sumMST += edge.cost;
        }
    }
}

void GraphImpl::MSTKruskalAdjList() {
    if (MSTtab) delete [] MSTtab;
    sumMST = 0;
    MSTtab = new MSTEdge [verticesNumber - 1];        //kazde drzewo rozpinajace ma dokladnie |V|-1 krawedzi
    int elem = 0;

    Set* set = new Set(verticesNumber);
    for (int i = 0; i < verticesNumber; i++) set->makeSet(i);       //dla kazdego wierzcholka tworzony jest set (z tym jednym wierzcholkiem)
    PriorityQueue* queue = new PriorityQueue(edgesNumber, verticesNumber, adjacencyList);
    for (int i = 0; i < edgesNumber; i++){
//        queueElement edge = queue->extractMin();
        MSTEdge edge = queue->extractMin();
        if (set->findSet(edge.tail) != set->findSet(edge.head)) {
            set->unionSets(edge.tail, edge.head);
            MSTtab[elem] = edge;
//            MSTtab[elem].tail = edge.tail;
//            MSTtab[elem].head = edge.head;
//            MSTtab[elem].cost = edge.cost;
            elem++;
            sumMST += edge.cost;
        }
    }

}

void GraphImpl::printMST() {
    std::cout << "MST: " << std::endl;
    std::cout << "Edge:   Weight:" << std::endl;
    if (!MSTtab) return;                            //jesli MST nie zostalo utorzone
    for (int i = 0; i < verticesNumber-1; i++) {
        MSTEdge edge = MSTtab[i];
        std::cout << "(" <<  edge.tail << ", " << edge.head << ")    " << edge.cost << std::endl;
    }
    //std::cout << "MST = " << sumMST() << std::endl;
    std::cout << "MST = " << sumMST << std::endl;
}

void GraphImpl::MSTPrimAdjMatrix(int r) {
    if (r < 0 || r > verticesNumber) return;
    delete [] MSTtab;
    sumMST = 0;
    MSTtab = new MSTEdge [verticesNumber-1];
    setNode* V = new setNode[verticesNumber];   //zbior wierzcholkow - indeks oznacza numer wierzcholka

    bool* visitedVertices = new bool[verticesNumber];    //zbior wierzcholkow ktorych juz nie ma w kolejce, zeby nie musiec iterowac po tablicy kopca
    for(int i = 0; i < verticesNumber; i++){
        visitedVertices[i] = false;
    }

    for(int u = 0; u < verticesNumber; u++){
        V[u].rank = INT_MAX;
        V[u].parent = -1;
    }
    V[r].parent = r;
    V[r].rank = 0;

    PriorityQueue* queue = new PriorityQueue(verticesNumber, V);
    int elem = 0;
    bool first = true;

    while (!queue->isEmpty()){
        MSTEdge edgeU = queue->extractMin();
        int u = edgeU.head;
        visitedVertices[u] = true;

        if (first) first = false;
        else {
            MSTtab[elem] = edgeU;
            sumMST+=edgeU.cost;
            elem++;

        }
        for (int v = 0; v < verticesNumber; v++){
            if (!visitedVertices[v] && adjacencyMatrix[u][v] < V[v].rank){
                V[v].rank = adjacencyMatrix[u][v];
                V[v].parent = u;
                queue->updateValues(v, adjacencyMatrix[u][v], u);
            }
        }   //mozna by bylo po for wywolac build-heap
    }
    delete [] V;
    delete [] visitedVertices;
}

void GraphImpl::MSTPrimAdjList(int r) {
    if (r < 0 || r > verticesNumber) return;
    delete [] MSTtab;
    sumMST = 0;
    MSTtab = new MSTEdge [verticesNumber-1];
    setNode* V = new setNode[verticesNumber];   //zbior wierzcholkow - indeks oznacza numer wierzcholka

    bool* visitedVertices = new bool[verticesNumber];    //zbior wierzcholkow ktorych juz nie ma w kolejce, zeby nie musiec iterowac po tablicy kopca
    for(int i = 0; i < verticesNumber; i++){
        visitedVertices[i] = false;
    }

    for(int u = 0; u < verticesNumber; u++){
        V[u].rank = INT_MAX;
        V[u].parent = -1;
    }
    V[r].parent = r;
    V[r].rank = 0;

//    std::cout << "Zbior wierzcholkow: " << std::endl;
//    for( int i = 0; i < verticesNumber; i++){
//        std::cout << i << ", " << V[i].parent << " : " << V[i].rank << std::endl;
//    }

    PriorityQueue* queue = new PriorityQueue(verticesNumber, V);
//    queue->printHeap();
    int elem = 0;
    bool first = true;

//    std::cout << std::endl << "kolejne wierzcholki z kolejki: " << std::endl;
    while (!queue->isEmpty()){
        MSTEdge edgeU = queue->extractMin();
        int u = edgeU.head;
        visitedVertices[u] = true;

//        std::cout << u << ": " << edgeU.tail << ", " << u << ":" << edgeU.cost << std::endl;
        if (first) first = false;
        else {
            MSTtab[elem] = edgeU;
            sumMST+=edgeU.cost;
            elem++;

        }

        listNode* v = adjacencyList[u];
        while(v) {
            if(!visitedVertices[v->vertex] && v->cost < V[v->vertex].rank){
                V[v->vertex].rank = v->cost;
                V[v->vertex].parent = u;
                queue->updateValues(v->vertex, v->cost, u);
            }
            v = v->next;
        }
//
//        for (int v = 0; v < verticesNumber; v++){
//            if (!visitedVertices[v] && adjacencyMatrix[u][v] < V[v].rank){
//                V[v].rank = adjacencyMatrix[u][v];
//                V[v].parent = u;
//                queue->updateValues(v, adjacencyMatrix[u][v], u);
//            }
//        }
//        queue->printHeap();
    }
    delete [] V;
    delete [] visitedVertices;

}

int GraphImpl::DFS() {
    int numTrees = 0;   //ilosc drzew, czyli osobnych sciezek

    color* colors = new color[verticesNumber];
    int* parents = new int[verticesNumber];
    int  time;

    for (int i = 0; i < verticesNumber; i++){
        colors[i] = WHITE;
        parents[i] = -1;
    }
    time = 0;

    for (int i = 0; i < verticesNumber; i++){
        if (colors[i] == WHITE) {
            DFSVisit(i, colors, parents, time);
            numTrees++;
        }
    }
    return numTrees;
}

void GraphImpl::DFSVisit(int u, color *&colors, int *&parents, int time) {
    int *d = new int[verticesNumber];
    int *f = new int[verticesNumber];

    colors[u] = GREY;
    d[u] = time = time+1;
    listNode* v = adjacencyList[u];
    while(v){
        if(colors[v->vertex] == WHITE){
            parents[v->vertex] = u;
            DFSVisit(v->vertex, colors, parents, time);
        }
        v = v->next;
    }
    colors[u] = BLACK;
    f[u] = time = time+1;


}

bool GraphImpl::isConnected() {
    if (DFS() > 1) return false;
    return true;
}
