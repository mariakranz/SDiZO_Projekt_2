//
// Created by szef on 21.05.2023.
//

#ifndef SDIZO_PROJEKT_2_SHORTESTPATHMENU_H
#define SDIZO_PROJEKT_2_SHORTESTPATHMENU_H



#include "../data/FileData.h"
#include "../graphs/DirectedGraph.h"

class ShortestPathMenu {
    int source;
    int verticesNum;
    void insertDataToTheGraph(FileData* fileData, DirectedGraph*& graph);
    void printShortestPath(setNode* V);
    void printPath(int startVertex, int endVertex, setNode* V);
public:
    ShortestPathMenu();
    void menu();
};


#endif //SDIZO_PROJEKT_2_SHORTESTPATHMENU_H
