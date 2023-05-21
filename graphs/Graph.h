//
// Created by szef on 21.05.2023.
//

#ifndef SDIZO_PROJEKT_2_GRAPH_H
#define SDIZO_PROJEKT_2_GRAPH_H
#define infinity INT_MAX

struct MSTEdge{             //krawedzie drzewa
    int tail, head, cost;
};

struct setNode{             //do klasy Set i PriorityQueue
    int rank, parent;
};

struct listNode{          //element listy sąsiedztwa
    int vertex, cost;
    listNode* next;
};


class Graph {

protected:
    int verticesNumber;
    int** adjacencyMatrix; //macierz sąsiedztwa - tablica dwuwymiarowa
    listNode** adjacencyList;   //lista sąsiedztwa - tablica list (tablica wskaznikow na struktury)
    int edgesNumber;
public:
    Graph(int verticesNumber, int edgesNumber);
    ~Graph();
    int** getAdjMatrix();
    listNode** getAdjList();
};


#endif //SDIZO_PROJEKT_2_GRAPH_H
