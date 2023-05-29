//
// Created by szef on 21.05.2023.
//

#include <iostream>
#include "GraphRepresentations.h"

void GraphRepresentations::printAdjacencyMatrix(int **table, int verticesNum) {
    std::cout << "Macierz sasiedztwa:" << std::endl;
    std::cout << "     ";
    for (int i = 0; i < verticesNum; i++){
        std::cout.width(5);
        std::cout << i;
    }
    std::cout << std::endl;

    for (int i = 0; i < verticesNum; i++) {
        std::cout.width(5);
        std::cout << i;
        for (int j = 0; j < verticesNum; j++){
            std::cout.width(5);
            int cost = table[i][j];
            if (cost == infinity) std::cout << "-";
            else std::cout << cost;
        }
        std::cout << std::endl;
    }

}

void GraphRepresentations::printAdjacencyList(listNode **listTable, int verticesNum) {
    std::cout << "Lista sasiedztwa:" << std::endl;
    for(int i = 0; i < verticesNum; i++ )
    {
        std::cout << i;
        listNode* node = listTable[i];
        while(node)
        {
            std::cout << "->";
            std::cout << node->vertex << "(" << node->cost << ")";
            node = node->next;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
