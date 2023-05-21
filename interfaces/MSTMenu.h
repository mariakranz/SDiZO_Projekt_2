//
// Created by szef on 21.05.2023.
//

#ifndef SDIZO_PROJEKT_2_MSTMENU_H
#define SDIZO_PROJEKT_2_MSTMENU_H


#include "../data/FileData.h"
#include "../graphs/UndirectedGraph.h"

class MSTMenu {
    int verticesNum;
    void insertDataToTheGraph(FileData* fileData, UndirectedGraph*& graph);

    void printMST(MSTEdge* MSTtab, int verticesNum);
public:
    MSTMenu();
    void menu();
};


#endif //SDIZO_PROJEKT_2_MSTMENU_H
