//
// Created by szef on 12.05.2023.
//

#ifndef SDIZO_PROJEKT_2_SET_H
#define SDIZO_PROJEKT_2_SET_H


#include "../graphs/Graph.h"

class Set{
    setNode* setsTable;                     //tablica setow czyli drzew
    int size;
    void link(int x, int y);
public:
    Set(int verticesNumber);
    ~Set();
    void makeSet(int x);
    void unionSets(int x, int y);
    int findSet(int x);

    void printSetsTable();                  //funkcja pomocnicza - wyswietlanie setow

};


#endif //SDIZO_PROJEKT_2_SET_H
