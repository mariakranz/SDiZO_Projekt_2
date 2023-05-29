//
// Created by szef on 22.05.2023.
//

#ifndef SDIZO_PROJEKT_2_TIMETESTS_H
#define SDIZO_PROJEKT_2_TIMETESTS_H

#define DENNUM 4
#define VERTNUM 5
#define NUMTINST 100

struct edgeT{int tail, head;};


class TimeTests {
    const int density[DENNUM] = {25, 50, 75, 99};
    const int vertNum [VERTNUM] = {10, 25, 50, 75, 100};
    const std::string directory = "";

    bool isEdgeTaken(int tail, int head, edgeT *&tab, int size);
    void printTakenEdges(edgeT *&tab, int size);

public:
    TimeTests();
    int testKruskalMatrix();
    int testKruskalList();
    int testPrimMatrix();
    int testPrimList();

    int testDijkstraMatrix();
    int testDijkstraList();
    int testBellmanFordMatrix();
    int testBellmanFordList();
};


#endif //SDIZO_PROJEKT_2_TIMETESTS_H
