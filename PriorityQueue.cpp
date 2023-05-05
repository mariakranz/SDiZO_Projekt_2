//
// Created by szef on 05.05.2023.
//

#include <iostream>
#include "PriorityQueue.h"

PriorityQueue::PriorityQueue(int edgesNumber, int verticesNumber, int** adjacencyMatrix) {
    this->size = edgesNumber;
    heapTable = new queueElement[size];

    int elem = 0;
    for (int i = 0; i < verticesNumber; i++){
        for (int j = i; j < verticesNumber; j++){           //w grafie nieskierowanym macierz po przekątnej jest symetryczna
            if(adjacencyMatrix[i][j] != INT_MAX){
                heapTable[elem].tail = i;
                heapTable[elem].head = j;
                heapTable[elem].cost = adjacencyMatrix[i][j];
                elem++;
            }
        }
    }

    buildMinHeap();
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
        queueElement tmpElem = heapTable[lowest];
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

queueElement PriorityQueue::extractMin() {
    if(size<1) return {};
    queueElement minElem = heapTable[0];
    heapTable[0] = heapTable[size-1];
    size--;
    heapify(0);
    queueElement *tmp = new queueElement[size];       //utworz nowy kopiec (o rozmiar mniejszy)
    for(int i = 0; i<size; i++){
        tmp[i] = heapTable[i];      //przepisz elementy ze starego kopca do nowego kopca
    }
    delete [] heapTable;
    heapTable = tmp;
    return minElem;
}

void PriorityQueue::printHeap() {
    std::cout << "Kopiec minimalny:" << std::endl;
    for(int i = 0; i < size; i++){
        queueElement edgeOnIndex = heapTable[i];
        std::cout << "(" <<  edgeOnIndex.tail << ", " << edgeOnIndex.head << ")    " << edgeOnIndex.cost << std::endl;
    }
}

PriorityQueue::PriorityQueue(int size) {
    this->size = 0;
    heapTable = nullptr;
//    this->size = size;
//    heapTable = new queueElement [size];
}

void PriorityQueue::addEdge(int tail, int head, int cost) {
//    size++;
//    queueElement *tmp = new queueElement[size];
//    for(int i = 0; i<size-1; i++){
//        tmp[i] = heapTable[i];
//    }
//    if (heapTable) delete [] heapTable;
//    heapTable = tmp;
//
//    int i = size -1;
//    while (i>0 && heapTable[parent(i)].tail < tail ){
//        heapTable[i] = heapTable[parent(i)];
//        i = parent(i);
//    }
//    heap[i] = key;
}

PriorityQueue::PriorityQueue(int edgesNumber, int verticesNumber, listNode **listTable) {
    this->size = edgesNumber;
    heapTable = new queueElement[size];

    int elem = 0;
    for (int i = 0; i < verticesNumber; i++){
        listNode* node = listTable[i];
        while (node){       //trzeba najpierw sprawdzic czy nie ma juz takiego wierzcholka w tablicy tylko z zamienionymi wierzcholkami
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

PriorityQueue::~PriorityQueue() {
    delete [] heapTable;
}
