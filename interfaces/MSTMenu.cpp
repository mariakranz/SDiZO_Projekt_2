//
// Created by szef on 21.05.2023.
//

#include <iostream>
#include "MSTMenu.h"
#include "GraphRepresentations.h"

using namespace std;

MSTMenu::MSTMenu() {
    verticesNum = 0;
}

void MSTMenu::menu() {
    char choice;
    UndirectedGraph *graph = nullptr;
    FileData* file = new FileData();
    std::string filePath;
    int vert;
    bool isConnected = false;

    do{
        cout << "\nWYZNACZANIE MST - MENU:\n"
                "1. Wczytanie grafu z pliku,\n"
                "2. Wyswietlenie grafu macierzowo i listowo,\n"
                "3. Algorytm Kruskala macierzowo i listowo z wyswietleniem wynikow,\n"
                "4. Algorytm Prima macierzowo i listowo z wyswietleniem wynikow.\n"
                "0. Wyjdz z menu.\n"
                "Wpisz numer: ";
        cin >> choice;

        switch (choice) {
            default:
                cout << "Nie ma takiej opcji!\n";
                break;
            case '0':
                break;
            case '1':       //wczytanie z pliku
                cout << "Podaj sciezke do pliku: ";
                cin >> filePath;
                if (file->readDataFromFile(filePath) == -1){
                    cout << "Nie mozna odczytac danych.\n";
                    break;
                }
                cout << "Dane odczytano z: " << filePath << endl;
                insertDataToTheGraph(file, graph);
                GraphRepresentations::printAdjacencyMatrix(graph->getAdjMatrix(), verticesNum);
                GraphRepresentations::printAdjacencyList(graph->getAdjList(), verticesNum);
                isConnected = graph->isConnected();
                break;

            case '2':       //wyswietlenie grafu
                if (graph != nullptr) {
                    GraphRepresentations::printAdjacencyMatrix(graph->getAdjMatrix(), verticesNum);
                    cout << endl;
                    GraphRepresentations::printAdjacencyList(graph->getAdjList(), verticesNum);
                }
                else cout << "Graf nie zostal zaladowany." << endl;
                break;
            case '3':       //algorytm 1
                if (graph != nullptr) {
                    if (isConnected) {              //jeszcze mozna zrobic sprawdzenie czy jest nieskierowany
                        cout << "Algorytm Kruskala." << endl;
                        cout << "Macierz sasiedztwa: " << endl;
                        printMST(graph->MSTKruskalAdjMatrix(), verticesNum);          //zrobic sortowanie - radix sort (po pierwszej a potem drugiej krawedzi)
                        cout << "Lista sasiedztwa:" << endl;
                        printMST(graph->MSTKruskalAdjList(), verticesNum);
                    }else cout  << "Graf jest niespojny!" << endl;
                }
                else cout << "Graf nie zostal zaladowany." << endl;
                break;

            case '4':       //algorytm 2
                if(graph!= nullptr) {
                    if (isConnected) {
                        cout << "Algorytm Prima." << endl;
                        cout << "Podaj wierzcholek:" << endl;
                        cin >> vert;
                        cout << "Macierz sasiedztwa: " << endl;
                        printMST(graph->MSTPrimAdjMatrix(vert), verticesNum);      //mozna by dodac inf zwrotna jesli wierzcholek jest nieprawidlowwy
                        cout << "Lista sasiedztwa: " << endl;
                        printMST(graph->MSTPrimAdjList(vert), verticesNum);
                    } else cout << "Graf jest niespojny!" << endl;
                }
                else cout << "Graf nie zostal zaladowany." << endl;
                break;
        }
        system("PAUSE");
    }while (choice != '0');

    delete file;
    delete graph;
}

void MSTMenu::insertDataToTheGraph(FileData *fileData, UndirectedGraph *&graph) {
    verticesNum = fileData->getVerticesNumber();
    graph = new UndirectedGraph(verticesNum, fileData->getEdgesNumber());
    edge* data = fileData->getEdges();
    for (int i = 0; i < fileData->getEdgesNumber(); i++) {
        edge edgeData = data[i];
        graph->addEdge(edgeData.tail, edgeData.head, edgeData.cost); //lepiej strukture tu zrobic, chociaz nwm bo wtedy bedzie private
    }
}

void MSTMenu::printMST(MSTEdge *MSTtab, int verticesNum) {
    if (MSTtab == nullptr or verticesNum < 1){
        cout << "Brak tablicy krawedzi lub nieprawidlowa liczba wierzcholkow." << endl;
        return;
    }
    int sumMST = 0;
    std::cout << "MST: " << std::endl;
    std::cout << "Edge:   Weight:" << std::endl;
    for (int i = 0; i < verticesNum-1; i++) {
        MSTEdge edge = MSTtab[i];
        std::cout << "(" <<  edge.tail << ", " << edge.head << ")    " << edge.cost << std::endl;
        sumMST += edge.cost;
    }
    std::cout << "MST = " << sumMST << std::endl;
}
