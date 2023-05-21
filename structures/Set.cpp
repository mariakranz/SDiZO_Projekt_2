//
// Created by szef on 12.05.2023.
//

#include <iostream>
#include "Set.h"

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