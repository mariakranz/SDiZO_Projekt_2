//
// Created by szef on 21.05.2023.
//

#ifndef SDIZO_PROJEKT_2_GRAPHREPRESENTATIONS_H
#define SDIZO_PROJEKT_2_GRAPHREPRESENTATIONS_H


#include "../graphs/Graph.h"

class GraphRepresentations {
public:
    static void printAdjacencyMatrix(int **table, int verticesNum);
    static void printAdjacencyList(listNode **listTable, int verticesNum);
};


#endif //SDIZO_PROJEKT_2_GRAPHREPRESENTATIONS_H
