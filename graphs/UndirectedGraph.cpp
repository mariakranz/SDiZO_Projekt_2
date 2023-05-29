//
// Created by szef on 21.05.2023.
//

#include "UndirectedGraph.h"
#include "../structures/PriorityQueue.h"

UndirectedGraph::UndirectedGraph(int verticesNumber, int edgesNumber) : Graph(verticesNumber, edgesNumber) {
    this->verticesNumber = verticesNumber;
    this->edgesNumber = edgesNumber;
}

void UndirectedGraph::addEdge(int tail, int head, int cost) {
    if(tail == head) {
        edgesNumber--;                                                                  //zalozenie, ze przy inicjalizacji podawana jest calkowita liczba krawedzi (nie uwzgledniajac powtorek i krawedzi wierzcholkow samych ze soba)
        return;                                                                         //jesli rowne to nie dodawaj
    }
    adjacencyMatrix[tail][head] = cost;                                                 //dodawanie do macierzy sasiedztwa
    adjacencyMatrix[head][tail] = cost;

    if(changeAlreadyDefinedEdge(tail, head, cost)) return;                              //jesli taka krawedz byla juz w grafie to ja nadpisz
                                                                                        //w przeciwnym wypadku stworz nowy wezel (nowe polaczenie)
    listNode* newNode = new listNode{head, cost, adjacencyList[tail]};
    adjacencyList[tail] = newNode;
    listNode *nextNewNode = new listNode{tail, cost, adjacencyList[head]};
    adjacencyList[head] = nextNewNode;
}

bool UndirectedGraph::changeAlreadyDefinedEdge(int tail, int head, int cost) {
    listNode* n = adjacencyList[tail];
    while(n){
        if(n->vertex == head) {                     //jesli zanjdzie juz definicje danej krawedzi
            n->cost = cost;                         //nadpisuje wage, nowa wartoscia

            listNode* p = adjacencyList[head];
            while(p->vertex != tail)p = p->next;    //ustaw p na element do nadpisania
            p->cost = cost;                         //nadpisuje wage
            edgesNumber--;
            return true;
        }
        n = n->next;
    }
    return false;
}

void UndirectedGraph::DFSVisit(int u, color *&colors, int *&parents, int time) {
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

int UndirectedGraph::DFS() {
    int numTrees = 0;                                                       //ilosc drzew, czyli osobnych sciezek

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

bool UndirectedGraph::isConnected() {
    if (DFS() > 1) return false;
    return true;
}

MSTEdge *UndirectedGraph::MSTKruskalAdjMatrix() {
    MSTEdge* MSTtab = new MSTEdge [verticesNumber - 1];                                 //kazde drzewo rozpinajace ma dokladnie |V|-1 krawedzi
    int elem = 0;

    Set* set = new Set(verticesNumber);
    for (int i = 0; i < verticesNumber; i++) set->makeSet(i);                       //dla kazdego wierzcholka tworzony jest set (z tym jednym wierzcholkiem)
    PriorityQueue* queue = new PriorityQueue(edgesNumber,verticesNumber,adjacencyMatrix);
    for (int i = 0; i < edgesNumber; i++){
        MSTEdge edge = queue->extractMin();
        if (set->findSet(edge.tail) != set->findSet(edge.head)) {
            set->unionSets(edge.tail, edge.head);
            MSTtab[elem] = edge;
            elem++;
        }
    }
    return MSTtab;
}

MSTEdge *UndirectedGraph::MSTKruskalAdjList() {
    MSTEdge* MSTtab = new MSTEdge [verticesNumber - 1];                             //kazde drzewo rozpinajace ma dokladnie |V|-1 krawedzi
    int elem = 0;

    Set* set = new Set(verticesNumber);
    for (int i = 0; i < verticesNumber; i++) set->makeSet(i);                   //dla kazdego wierzcholka tworzony jest set (z tym jednym wierzcholkiem)
    PriorityQueue* queue = new PriorityQueue(edgesNumber, verticesNumber, adjacencyList);
    for (int i = 0; i < edgesNumber; i++){
        MSTEdge edge = queue->extractMin();
        if (set->findSet(edge.tail) != set->findSet(edge.head)) {
            set->unionSets(edge.tail, edge.head);
            MSTtab[elem] = edge;
            elem++;
        }
    }
    return MSTtab;
}

MSTEdge *UndirectedGraph::MSTPrimAdjMatrix(int r) {
    if (r < 0 || r > verticesNumber - 1) return nullptr;
    MSTEdge* MSTtab = new MSTEdge [verticesNumber-1];
    setNode* V = new setNode[verticesNumber];                                       //zbior wierzcholkow - indeks oznacza numer wierzcholka

    bool* visitedVertices = new bool[verticesNumber];                               //zbior wierzcholkow ktorych juz nie ma w kolejce, zeby nie musiec iterowac po tablicy kopca
    for(int i = 0; i < verticesNumber; i++){
        visitedVertices[i] = false;
    }

    for(int u = 0; u < verticesNumber; u++){
        V[u].rank = infinity;
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
    return MSTtab;
}

MSTEdge *UndirectedGraph::MSTPrimAdjList(int r) {
    if (r < 0 || r > verticesNumber - 1) return nullptr;
    MSTEdge* MSTtab = new MSTEdge [verticesNumber-1];
    setNode* V = new setNode[verticesNumber];                               //zbior wierzcholkow - indeks oznacza numer wierzcholka

    bool* visitedVertices = new bool[verticesNumber];                       //zbior wierzcholkow ktorych juz nie ma w kolejce, zeby nie musiec iterowac po tablicy kopca
    for(int i = 0; i < verticesNumber; i++){
        visitedVertices[i] = false;
    }

    for(int u = 0; u < verticesNumber; u++){
        V[u].rank = infinity;
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

        if (first) first = false;                                               //pierwszego wierzcholka nie dodawaj do listy krawedzi
        else {
            MSTtab[elem] = edgeU;
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
    }
    delete [] V;
    delete [] visitedVertices;
    return MSTtab;
}
