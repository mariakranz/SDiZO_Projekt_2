//
// Created by szef on 21.05.2023.
//

#include <iostream>
#include "ShortestPathMenu.h"
#include "GraphRepresentations.h"

using namespace std;

void ShortestPathMenu::menu(){
    char choice;
    DirectedGraph* graph = nullptr;
    FileData* file = new FileData();
    string filePath;

    do{
        cout << "WYZNACZANIE NAJKROTSZEJ SCIEZKI W GRAFIE - MENU:\n"
                "1. Wczytanie grafu z pliku,\n"
                "2. Wyswietlenie grafu macierzowo i listowo,\n"
                "3. Algorytm Dijkstry macierzowo i listowo z wyswietleniem wynikow,\n"
                "4. Algorytm Bellmana-Forda macierzowo i listowo z wyswietleniem wynikow.\n"
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
                //cin >> filePath;
                filePath = "C:\\Users\\szef\\CLionProjects\\SDiZO-Projekt-2\\data\\data7.txt";
                if (file->readDataFromFile(filePath) == -1){
                    cout << "Nie mozna odczytac danych.\n";
                    break;
                }
                cout << "Dane odczytano z: " << filePath << endl;
                insertDataToTheGraph(file, graph);
                GraphRepresentations::printAdjacencyMatrix(graph->getAdjMatrix(), verticesNum);
                GraphRepresentations::printAdjacencyList(graph->getAdjList(), verticesNum);
                break;
            case '2':       //wyswietlenie grafu
                if (graph != nullptr) {
                    GraphRepresentations::printAdjacencyMatrix(graph->getAdjMatrix(), verticesNum);
                    cout << endl;
                    GraphRepresentations::printAdjacencyList(graph->getAdjList(), verticesNum);
                }else cout << "Graf nie zostal zaladowany." << endl;
                break;
            case '3':       //algorytm 1
                if(graph != nullptr){
                    if(graph->areAllWagesPositive()){
                        cout << "Algorytm Dijkstry." << endl;
                        cout << "Macierz sasiedztwa:" << endl;
                        printShortestPath(graph->DijkstraAdjMatrix(source));
                        cout << "Lista sasiedztwa:" << endl;
                        printShortestPath(graph->DijkstraAdjList(source));
                    }else cout << "W grafie znajduja sie ujemne wagi." << endl;
                }else cout << "Graf nie zostal zaladowany." << endl;
                break;

            case '4':       //algorytm 2
                if(graph != nullptr){
                    cout << "Algorytm Bellmana-Forda." << endl;
                    cout << "Macierz sasiedztwa:" << endl;
                    printShortestPath(graph->BellmanFordAdjMatrix(source));
                    cout << "Lista sasiedztwa:" << endl;
                    printShortestPath(graph->BellmanFordAdjList(source));
                }else cout << "Graf nie zostal zaladowany." << endl;
                break;
        }
        system("PAUSE");
    }while (choice != '0');

    delete file;
    delete graph;
}

void ShortestPathMenu::insertDataToTheGraph(FileData *fileData, DirectedGraph *&graph) {
    source = fileData->getStartVertex();
    verticesNum = fileData->getVerticesNumber();
    graph = new DirectedGraph(verticesNum, fileData->getEdgesNumber());
    edge* data = fileData->getEdges();
    for (int i = 0; i < fileData->getEdgesNumber(); i++) {
        edge edgeData = data[i];
        graph->addEdge(edgeData.tail, edgeData.head, edgeData.cost);
    }
}

void ShortestPathMenu::printShortestPath(setNode* V) {
    if (V == nullptr) {
        cout << "Brak tablicy wierzcholkow." << endl;
        return;
    }
    std::cout << "Znajdowanie najkrotszej sciezki: " << std::endl;
    std::cout << "Start = " << source << std::endl;
    std::cout << "End  " << "Dist " << " Path" << std::endl;
    for (int i = 0; i < verticesNum; i++) {
        std::cout.width(4);
        std::cout << i << "|";
        std::cout.width(4);
        if (V[i].rank == infinity) {
            std::cout << "  - |";
        } else {
            std::cout << V[i].rank << "|";
            printPath(i, source, V);
        }
        std::cout << std::endl;
    }
}

ShortestPathMenu::ShortestPathMenu() {
    source = -1;
    verticesNum = 0;
}

void ShortestPathMenu::printPath(int startVertex, int endVertex, setNode* V) {
    if (startVertex != endVertex) printPath(V[startVertex].parent, endVertex, V);
    std::cout.width(4) ;
    std::cout << startVertex;
}



