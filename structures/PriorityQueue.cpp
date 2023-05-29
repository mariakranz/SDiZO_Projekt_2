//
// Created by szef on 05.05.2023.
//

#include <iostream>
#include "PriorityQueue.h"

PriorityQueue::PriorityQueue(int edgesNumber, int verticesNumber, int** adjacencyMatrix) {
    this->size = edgesNumber;
    heapTable = new MSTEdge[size];

    int elem = 0;
    for (int i = 0; i < verticesNumber; i++){
        for (int j = i; j < verticesNumber; j++){                       //w grafie nieskierowanym macierz po przekątnej jest symetryczna
            if(adjacencyMatrix[i][j] != infinity){
                heapTable[elem].tail = i;
                heapTable[elem].head = j;
                heapTable[elem].cost = adjacencyMatrix[i][j];
                elem++;
            }
        }
    }

    buildMinHeap();
}

PriorityQueue::PriorityQueue(int edgesNumber, int verticesNumber, listNode **listTable) {
    this->size = edgesNumber;
    heapTable = new MSTEdge[size];

    int elem = 0;
    for (int i = 0; i < verticesNumber; i++){
        listNode* node = listTable[i];
        while (node){
            if (node->vertex >= i) {
                heapTable[elem].tail = i;
                heapTable[elem].head = node->vertex;
                heapTable[elem].cost = node->cost;
                elem++;
            }
            node = node->next;
        }
    }
    buildMinHeap();
}

PriorityQueue::PriorityQueue(int verticesNumber, setNode *vertices) {
    this->size = verticesNumber;
    heapTable = new MSTEdge[size];

    for(int i = 0; i < verticesNumber; i++){
        heapTable[i].head = i;
        heapTable[i].tail = vertices[i].parent;
        heapTable[i].cost = vertices[i].rank;
    }
    buildMinHeap();
}

PriorityQueue::~PriorityQueue() {
    delete [] heapTable;
}

void PriorityQueue::buildMinHeap() {
    for (int i = (size/2) - 1; i >= 0 ; i--){
        heapify(i);
    }

}

void PriorityQueue::heapify(int index) {
    int l = left(index);
    int r = right(index);
    int lowest;
    if (l<size && heapTable[l].cost < heapTable[index].cost){
        lowest = l;
    }else{
        lowest = index;
    }
    if (r<size && heapTable[r].cost < heapTable[lowest].cost){
        lowest = r;
    }
    if (lowest != index){
        MSTEdge tmpElem = heapTable[lowest];
        heapTable[lowest] = heapTable[index];
        heapTable[index] = tmpElem;
        heapify(lowest);
    }
}

int PriorityQueue::parent(int index) {
    return (index-1) / 2;
}

int PriorityQueue::left(int index) {
    return 2 * index + 1;
}

int PriorityQueue::right(int index) {
    return 2 * index + 2;
}

MSTEdge PriorityQueue::extractMin() {
    if(size<1) return {};
    MSTEdge minElem = heapTable[0];
    heapTable[0] = heapTable[size-1];
    size--;
    heapify(0);
    MSTEdge *tmp = new MSTEdge[size];               //utworz nowy kopiec (o rozmiar mniejszy)
    for(int i = 0; i<size; i++){
        tmp[i] = heapTable[i];                      //przepisz elementy ze starego kopca do nowego kopca
    }
    delete [] heapTable;
    heapTable = tmp;
    return minElem;
}

void PriorityQueue::printHeap() {
    std::cout << "Kopiec minimalny:" << std::endl;
    for(int i = 0; i < size; i++){
        MSTEdge edgeOnIndex = heapTable[i];
        std::cout << "(" <<  edgeOnIndex.tail << ", " << edgeOnIndex.head << ")    " << edgeOnIndex.cost << std::endl;
    }
}

bool PriorityQueue::isEmpty() {
    if (size == 0) return true;
    return false;
}

int PriorityQueue::thisVertexIsInQueue(int v) {
    for(int i = 0; i < size; i++){
        if(heapTable[i].head == v) return i;
    }
    return -1;
}

int PriorityQueue::updateValues(int vertex, int key, int parent) {
    int index = thisVertexIsInQueue(vertex);
    if (index == -1) return -1;
    heapTable[index].cost = key;
    heapTable[index].tail = parent;
//    heapify(index);
    buildMinHeap();
    return 0;
}

