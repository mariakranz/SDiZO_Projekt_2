//
// Created by szef on 22.05.2023.
//


#include <iostream>
#include <chrono>

#include <fstream>
#include <random>
#include "TimeTests.h"
#include "../graphs/DirectedGraph.h"
#include "../graphs/UndirectedGraph.h"

using namespace std;

TimeTests::TimeTests() {

}

int TimeTests::testKruskalMatrix() {
    string filename = "KruskalMatrix_results.txt";

    string fullpath = directory + filename;
    ofstream file;
    file.open(fullpath, std::ios::out);
    if(file.is_open()){
        file << "density";                          //wpisywanie wiersza naglowkowego
        for(int i = 0; i < VERTNUM; i++){
            file << ";size" << vertNum[i];
        }
        file << endl;

        for(int i = 0; i < DENNUM; i++){
            for (int k = 0; k < NUMTINST; k++){
                file << density[i];
                for (int j = 0; j < VERTNUM; j++){
                    int verticesNum = vertNum[j];
                    int maxUndirectedEdges = (verticesNum * (verticesNum - 1)) / 2;
                    int edgesNum = maxUndirectedEdges * density[i] / 100;

                    UndirectedGraph* graph = new UndirectedGraph(verticesNum, edgesNum);

                    edgeT* takenEdges = new edgeT[edgesNum];
                    int edgeNR = 0;
                    int tail;
                    int head;


                    for(int ver = 0; ver < verticesNum; ver++){
                        tail = ver;
                        if(ver+1 == verticesNum) {
                            head = 0;
                        }else{
                            head = ver+1;
                        }
                        takenEdges[edgeNR++] = {tail, head};
                        graph->addEdge(tail, head, rand() % edgesNum + 1);
                    }

                    for(; edgeNR < edgesNum; edgeNR++){
                        do{
                            tail = rand() %verticesNum;
                            do{
                                head = rand() %verticesNum;
                            }while(tail == head);

                        }while (isEdgeTaken(tail, head, takenEdges, edgesNum) or isEdgeTaken(head, tail, takenEdges, edgesNum)); //chyba lepiej by bylo przeiterowac liste sasiedztwa
                        takenEdges[edgeNR] = {tail, head};
                        graph->addEdge(tail, head, rand() % edgesNum + 1);
                    }

                    std::cout << "Graf " << k << " - density: " << density[i] << "rozmiar: " << vertNum[j] << endl;
                    std::cout << "Spojny? ";
                    if(graph->isConnected()) std::cout << "tak" << endl;
                    else std::cout << "nie" << endl;

                    auto start = std::chrono::high_resolution_clock::now();
                    graph->MSTKruskalAdjMatrix();
                    auto end = std::chrono::high_resolution_clock::now();

                    long dur = (long)std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

                    std::cout << "Czas wykonania: " << dur << " nanosekundy" << std::endl;
                    file << ";" << dur;

                    delete graph;
                    delete [] takenEdges;
                }
                file << endl;
            }
        }
    }else {
        cout << "Nie udalo sie odtworzyc pliku." << endl;
        return - 1;
    }

    file.close();
    return 0;
}

int TimeTests::testKruskalList() {
    string filename = "KruskalList_results.txt";

    string fullpath = directory + filename;
    ofstream file;
    file.open(fullpath, std::ios::out);
    if(file.is_open()){
        file << "density";                          //wpisywanie wiersza naglowkowego
        for(int i = 0; i < VERTNUM; i++){
            file << ";size" << vertNum[i];
        }
        file << endl;

        for(int i = 0; i < DENNUM; i++){
            for (int k = 0; k < NUMTINST; k++){
                file << density[i];
                for (int j = 0; j < VERTNUM; j++){
                    int verticesNum = vertNum[j];
                    int maxUndirectedEdges = (verticesNum * (verticesNum - 1)) / 2;
                    int edgesNum = maxUndirectedEdges * density[i] / 100;

                    UndirectedGraph* graph = new UndirectedGraph(verticesNum, edgesNum);

                    edgeT* takenEdges = new edgeT[edgesNum];
                    int edgeNR = 0;
                    int tail;
                    int head;


                    for(int ver = 0; ver < verticesNum; ver++){
                        tail = ver;
                        if(ver+1 == verticesNum) {
                            head = 0;
                        }else{
                            head = ver+1;
                        }
                        takenEdges[edgeNR++] = {tail, head};
                        graph->addEdge(tail, head, rand() % edgesNum + 1);
                    }

                    for(; edgeNR < edgesNum; edgeNR++){
                        do{
                            tail = rand() %verticesNum;
                            do{
                                head = rand() %verticesNum;
                            }while(tail == head);

                        }while (isEdgeTaken(tail, head, takenEdges, edgesNum) or isEdgeTaken(head, tail, takenEdges, edgesNum));
                        takenEdges[edgeNR] = {tail, head};
                        graph->addEdge(tail, head, rand() % edgesNum + 1);
                    }

                    std::cout << "Graf " << k << " - density: " << density[i] << "rozmiar: " << vertNum[j] << endl;
                    std::cout << "Spojny? ";
                    if(graph->isConnected()) std::cout << "tak" << endl;
                    else std::cout << "nie" << endl;

                    auto start = std::chrono::high_resolution_clock::now();
                    graph->MSTKruskalAdjList();                       //ostatnio dodany wierzcholek z ktorego wychodzi krawedz
                    auto end = std::chrono::high_resolution_clock::now();

                    long dur = (long)std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

                    std::cout << "Czas wykonania: " << dur << " nanosekundy" << std::endl;
                    file << ";" << dur;

                    delete graph;
                    delete [] takenEdges;
                }
                file << endl;
            }
        }
    }else {
        cout << "Nie udalo sie odtworzyc pliku." << endl;
        return - 1;
    }

    file.close();
    return 0;
}

int TimeTests::testPrimMatrix() {
    string filename = "PrimMatrix_results.txt";

    string fullpath = directory + filename;
    ofstream file;
    file.open(fullpath, std::ios::out);
    if(file.is_open()){
        file << "density";                          //wpisywanie wiersza naglowkowego
        for(int i = 0; i < VERTNUM; i++){
            file << ";size" << vertNum[i];
        }
        file << endl;

        for(int i = 0; i < DENNUM; i++){
            for (int k = 0; k < NUMTINST; k++){
                file << density[i];
                for (int j = 0; j < VERTNUM; j++){
                    int verticesNum = vertNum[j];
                    int maxUndirectedEdges = (verticesNum * (verticesNum - 1)) / 2;
                    int edgesNum = maxUndirectedEdges * density[i] / 100;

                    UndirectedGraph* graph = new UndirectedGraph(verticesNum, edgesNum);

                    edgeT* takenEdges = new edgeT[edgesNum];
                    int edgeNR = 0;
                    int tail;
                    int head;


                    for(int ver = 0; ver < verticesNum; ver++){
                        tail = ver;
                        if(ver+1 == verticesNum) {
                            head = 0;
                        }else{
                            head = ver+1;
                        }
                        takenEdges[edgeNR++] = {tail, head};
                        graph->addEdge(tail, head, rand() % edgesNum + 1);
                    }

                    for(; edgeNR < edgesNum; edgeNR++){
                        do{
                            tail = rand() %verticesNum;
                            do{
                                head = rand() %verticesNum;
                            }while(tail == head);

                        }while (isEdgeTaken(tail, head, takenEdges, edgesNum) or isEdgeTaken(head, tail, takenEdges, edgesNum));
                        takenEdges[edgeNR] = {tail, head};
                        graph->addEdge(tail, head, rand() % edgesNum + 1);
                    }

                    std::cout << "Graf " << k << " - density: " << density[i] << "rozmiar: " << vertNum[j] << endl;
                    std::cout << "Spojny? ";
                    if(graph->isConnected()) std::cout << "tak" << endl;
                    else std::cout << "nie" << endl;

                    auto start = std::chrono::high_resolution_clock::now();
                    graph->MSTPrimAdjMatrix(rand() % verticesNum);                       //ostatnio dodany wierzcholek z ktorego wychodzi krawedz
                    auto end = std::chrono::high_resolution_clock::now();

                    long dur = (long)std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

                    std::cout << "Czas wykonania: " << dur << " nanosekundy" << std::endl;
                    file << ";" << dur;

                    delete graph;
                    delete [] takenEdges;
                }
                file << endl;
            }
        }
    }else {
        cout << "Nie udalo sie odtworzyc pliku." << endl;
        return - 1;
    }

    file.close();
    return 0;
}

int TimeTests::testPrimList() {
    string filename = "PrimList_results.txt";

    string fullpath = directory + filename;
    ofstream file;
    file.open(fullpath, std::ios::out);
    if(file.is_open()){
        file << "density";                          //wpisywanie wiersza naglowkowego
        for(int i = 0; i < VERTNUM; i++){
            file << ";size" << vertNum[i];
        }
        file << endl;

        for(int i = 0; i < DENNUM; i++){
            for (int k = 0; k < NUMTINST; k++){
                file << density[i];
                for (int j = 0; j < VERTNUM; j++){
                    int verticesNum = vertNum[j];
                    int maxUndirectedEdges = (verticesNum * (verticesNum - 1)) / 2;
                    int edgesNum = maxUndirectedEdges * density[i] / 100;

                    UndirectedGraph* graph = new UndirectedGraph(verticesNum, edgesNum);

                    edgeT* takenEdges = new edgeT[edgesNum];
                    int edgeNR = 0;
                    int tail;
                    int head;


                    for(int ver = 0; ver < verticesNum; ver++){
                        tail = ver;
                        if(ver+1 == verticesNum) {
                            head = 0;
                        }else{
                            head = ver+1;
                        }
                        takenEdges[edgeNR++] = {tail, head};
                        graph->addEdge(tail, head, rand() % edgesNum + 1);
                    }

                    for(; edgeNR < edgesNum; edgeNR++){
                        do{
                            tail = rand() %verticesNum;
                            do{
                                head = rand() %verticesNum;
                            }while(tail == head);

                        }while (isEdgeTaken(tail, head, takenEdges, edgesNum) or isEdgeTaken(head, tail, takenEdges, edgesNum));
                        takenEdges[edgeNR] = {tail, head};
                        graph->addEdge(tail, head, rand() % edgesNum + 1);
                    }

                    std::cout << "Graf " << k << " - density: " << density[i] << "rozmiar: " << vertNum[j] << endl;
                    std::cout << "Spojny? ";
                    if(graph->isConnected()) std::cout << "tak" << endl;
                    else std::cout << "nie" << endl;

                    auto start = std::chrono::high_resolution_clock::now();
                    graph->MSTPrimAdjList(rand() % verticesNum);                       //ostatnio dodany wierzcholek z ktorego wychodzi krawedz
                    auto end = std::chrono::high_resolution_clock::now();

                    long dur = (long)std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

                    std::cout << "Czas wykonania: " << dur << " nanosekundy" << std::endl;
                    file << ";" << dur;

                    delete graph;
                    delete [] takenEdges;
                }
                file << endl;
            }
        }
    }else {
        cout << "Nie udalo sie odtworzyc pliku." << endl;
        return - 1;
    }

    file.close();
    return 0;
}

int TimeTests::testDijkstraMatrix() {
    string filename = "DijkstraMatrix_results.txt";

    string fullpath = directory + filename;
    ofstream file;
    file.open(fullpath, std::ios::out);
    if(file.is_open()){
        file << "density";                          //wpisywanie wiersza naglowkowego
        for(int i = 0; i < VERTNUM; i++){
            file << ";size" << vertNum[i];
        }
        file << endl;

        for(int i = 0; i < DENNUM; i++){
            for (int k = 0; k < NUMTINST; k++){
                file << density[i];
                for (int j = 0; j < VERTNUM; j++){
                    int verticesNum = vertNum[j];
                    int maxUndirectedEdges = (verticesNum * (verticesNum - 1));
                    int edgesNum = maxUndirectedEdges * density[i] / 100;

                    DirectedGraph* graph = new DirectedGraph(verticesNum, edgesNum);

                    edgeT* takenEdges = new edgeT[edgesNum];
                    int edgeNR = 0;
                    int tail;
                    int head;

                    for(; edgeNR < edgesNum; edgeNR++){
                        do{
                            tail = rand() %verticesNum;
                            do{
                                head = rand() %verticesNum;
                            }while(tail == head);

                        }while (isEdgeTaken(tail, head, takenEdges, edgesNum));
                        takenEdges[edgeNR] = {tail, head};
                        graph->addEdge(tail, head, rand() % edgesNum + 1);
                    }

                    std::cout << "Graf " << k << " - density: " << density[i] << "rozmiar: " << vertNum[j] << endl;

                    auto start = std::chrono::high_resolution_clock::now();
                    graph->DijkstraAdjMatrix(rand() % verticesNum);                       //ostatnio dodany wierzcholek z ktorego wychodzi krawedz
                    auto end = std::chrono::high_resolution_clock::now();

                    long dur = (long)std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

                    std::cout << "Czas wykonania: " << dur << " nanosekundy" << std::endl;
                    file << ";" << dur;

                    delete graph;
                    delete [] takenEdges;
                }
                file << endl;
            }
        }
    }else {
        cout << "Nie udalo sie odtworzyc pliku." << endl;
        return - 1;
    }

    file.close();
    return 0;
}

int TimeTests::testDijkstraList() {
    string filename = "DijkstraList_results.txt";

    string fullpath = directory + filename;
    ofstream file;
    file.open(fullpath, std::ios::out);
    if(file.is_open()){
        file << "density";                          //wpisywanie wiersza naglowkowego
        for(int i = 0; i < VERTNUM; i++){
            file << ";size" << vertNum[i];
        }
        file << endl;

        for(int i = 0; i < DENNUM; i++){
            for (int k = 0; k < NUMTINST; k++){
                file << density[i];
                for (int j = 0; j < VERTNUM; j++){
                    int verticesNum = vertNum[j];
                    int maxUndirectedEdges = (verticesNum * (verticesNum - 1));
                    int edgesNum = maxUndirectedEdges * density[i] / 100;

                    DirectedGraph* graph = new DirectedGraph(verticesNum, edgesNum);

                    edgeT* takenEdges = new edgeT[edgesNum];
                    int edgeNR = 0;
                    int tail;
                    int head;

                    for(; edgeNR < edgesNum; edgeNR++){
                        do{
                            tail = rand() %verticesNum;
                            do{
                                head = rand() %verticesNum;
                            }while(tail == head);

                        }while (isEdgeTaken(tail, head, takenEdges, edgesNum));
                        takenEdges[edgeNR] = {tail, head};
                        graph->addEdge(tail, head, rand() % edgesNum + 1);
                    }

                    std::cout << "Graf " << k << " - density: " << density[i] << "rozmiar: " << vertNum[j] << endl;

                    auto start = std::chrono::high_resolution_clock::now();
                    graph->DijkstraAdjList(rand() % verticesNum);                       //ostatnio dodany wierzcholek z ktorego wychodzi krawedz
                    auto end = std::chrono::high_resolution_clock::now();

                    long dur = (long)std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

                    std::cout << "Czas wykonania: " << dur << " nanosekundy" << std::endl;
                    file << ";" << dur;

                    delete graph;
                    delete [] takenEdges;
                }
                file << endl;
            }
        }
    }else {
        cout << "Nie udalo sie odtworzyc pliku." << endl;
        return - 1;
    }

    file.close();
    return 0;
}


bool TimeTests::isEdgeTaken(int tail, int head, edgeT *&tab, int size) {
    for(int i = 0; i < size; i++){
        if(tab[i].head == head && tab[i].tail == tail) return true;
    }
    return false;
}

void TimeTests::printTakenEdges(edgeT *&tab, int size) {
    cout << "Edges" << endl;
    for (int i = 0; i < size; i++){
        cout << tab[i].tail << "," << tab[i].head << endl;
    }
}

int TimeTests::testBellmanFordMatrix() {
    string filename = "BellmanFordMatrix_results.txt";

    std::random_device rseed;
    std::mt19937 rng(rseed());


    string fullpath = directory + filename;
    ofstream file;
    file.open(fullpath, std::ios::out);
    if(file.is_open()){
        file << "density";                          //wpisywanie wiersza naglowkowego
        for(int i = 0; i < VERTNUM; i++){
            file << ";size" << vertNum[i];
        }
        file << endl;

        for(int i = 0; i < DENNUM; i++){
            for (int k = 0; k < NUMTINST; k++){
                file << density[i];
                for (int j = 0; j < VERTNUM; j++){
                    int verticesNum = vertNum[j];
                    int maxUndirectedEdges = (verticesNum * (verticesNum - 1));
                    int edgesNum = maxUndirectedEdges * density[i] / 100;

                    std::uniform_int_distribution<int> dist(-edgesNum,edgesNum);

                    DirectedGraph* graph = new DirectedGraph(verticesNum, edgesNum);

                    edgeT* takenEdges = new edgeT[edgesNum];
                    int edgeNR = 0;
                    int tail;
                    int head;

                    for(; edgeNR < edgesNum; edgeNR++){
                        do{
                            tail = rand() %verticesNum;
                            do{
                                head = rand() %verticesNum;
                            }while(tail == head);

                        }while (isEdgeTaken(tail, head, takenEdges, edgesNum));
                        takenEdges[edgeNR] = {tail, head};
                        graph->addEdge(tail, head, dist(rng));
                    }

                    std::cout << "Graf " << k << " - density: " << density[i] << "rozmiar: " << vertNum[j] << endl;

                    auto start = std::chrono::high_resolution_clock::now();
                    graph->BellmanFordAdjMatrix(rand() % verticesNum);
                    auto end = std::chrono::high_resolution_clock::now();

                    long dur = (long)std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

                    std::cout << "Czas wykonania: " << dur << " nanosekundy" << std::endl;
                    file << ";" << dur;

                    delete graph;
                    delete [] takenEdges;
                }
                file << endl;
            }
        }
    }else {
        cout << "Nie udalo sie odtworzyc pliku." << endl;
        return - 1;
    }

    file.close();
    return 0;
}

int TimeTests::testBellmanFordList() {
    string filename = "BellmanFordList_results.txt";

    std::random_device rseed;
    std::mt19937 rng(rseed());


    string fullpath = directory + filename;
    ofstream file;
    file.open(fullpath, std::ios::out);
    if(file.is_open()){
        file << "density";                          //wpisywanie wiersza naglowkowego
        for(int i = 0; i < VERTNUM; i++){
            file << ";size" << vertNum[i];
        }
        file << endl;

        for(int i = 0; i < DENNUM; i++){
            for (int k = 0; k < NUMTINST; k++){
                file << density[i];
                for (int j = 0; j < VERTNUM; j++){
                    int verticesNum = vertNum[j];
                    int maxUndirectedEdges = (verticesNum * (verticesNum - 1));
                    int edgesNum = maxUndirectedEdges * density[i] / 100;

                    std::uniform_int_distribution<int> dist(-edgesNum,edgesNum);

                    DirectedGraph* graph = new DirectedGraph(verticesNum, edgesNum);

                    edgeT* takenEdges = new edgeT[edgesNum];
                    int edgeNR = 0;
                    int tail;
                    int head;

                    for(; edgeNR < edgesNum; edgeNR++){
                        do{
                            tail = rand() %verticesNum;
                            do{
                                head = rand() %verticesNum;
                            }while(tail == head);

                        }while (isEdgeTaken(tail, head, takenEdges, edgesNum));
                        takenEdges[edgeNR] = {tail, head};
                        graph->addEdge(tail, head, dist(rng));
                    }

                    std::cout << "Graf " << k << " - density: " << density[i] << "rozmiar: " << vertNum[j] << endl;

                    auto start = std::chrono::high_resolution_clock::now();
                    graph->BellmanFordAdjList(rand() % verticesNum);
                    auto end = std::chrono::high_resolution_clock::now();

                    long dur = (long)std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

                    std::cout << "Czas wykonania: " << dur << " nanosekundy" << std::endl;
                    file << ";" << dur;

                    delete graph;
                    delete [] takenEdges;
                }
                file << endl;
            }
        }
    }else {
        cout << "Nie udalo sie odtworzyc pliku." << endl;
        return - 1;
    }

    file.close();
    return 0;
}








