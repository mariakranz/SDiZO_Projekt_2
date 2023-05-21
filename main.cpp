#include <iostream>
#include "GraphImpl.h"
#include "FileData.h"

using namespace std;

void menu();
void menu1();
void menu2();
void menu3();
void menu1FileRead(FileData* fileData, GraphImpl*& graph);


int main() {
    menu();
    return 0;
}

void menu(){
    char choice;

    do{
        cout << "\n----MENU----\n"
                "1. Wyznaczanie minimalnego drzewa rozpinajacego (MST).\n"
                "2. Wyznaczanie najkrotszej sciezki w grafie.\n"
                "3. Wyznaczanie maksymalnego przeplywu.\n"
                "0. Wyjdz z programu.\n"
                "Wprowdz numer: ";
        cin >> choice;
        switch (choice) {
            default:
                cout << "Nie ma takiej opcji!\n";
                break;
            case '0': break;
            case '1':
                menu1();
                break;
            case '2':
                menu2();
                break;
            case '3':
                menu3();
                break;
        }
    }while (choice != '0');
}

void menu1(){
    char choice;
    GraphImpl *graph = nullptr;
    FileData* file = new FileData();
    string filePath;
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
                //cin >> filePath;
                filePath = "C:\\Users\\szef\\CLionProjects\\SDiZO-Projekt-2\\data3.txt";
                if (file->readDataFromFile(filePath) == -1){
                    cout << "Nie mozna odczytac danych.\n";
                    break;
                }
                cout << "Dane odczytano z: " << filePath << endl;
                menu1FileRead(file, graph);
                graph->printAdjacencyMatrix();
                graph->printAdjacencyList();
                isConnected = graph->isConnected();
                break;

            case '2':       //wyswietlenie grafu
                if (graph != nullptr) {
                    graph->printAdjacencyMatrix();
                    graph->printAdjacencyList();
                }
                else cout << "Graf nie zostal zaladowany." << endl;
                break;
            case '3':       //algorytm 1
                if (graph != nullptr) {
                    if (isConnected) {
                        cout << "Macierz sasiedztwa: " << endl;
                        graph->MSTKruskalAdjMatrix();
                        graph->printMST();          //zrobic sortowanie - radix sort (po pierwszej a potem drugiej krawedzi)
                        cout << "Lista sasiedztwa:" << endl;
                        graph->MSTKruskalAdjList();
                        graph->printMST();
                    }else cout  << "Graf jest niespojny!" << endl;
                }
                else cout << "Graf nie zostal zaladowany." << endl;
                break;

            case '4':       //algorytm 2
                if(graph!= nullptr) {
                    if (isConnected) {
                        cout << "Podaj wierzcholek:" << endl;
                        cin >> vert;
                        cout << "Macierz sasiedztwa: " << endl;
                        graph->MSTPrimAdjMatrix(vert);      //mozna by dodac inf zwrotna jesli wierzcholek jest nieprawidlowwy
                        graph->printMST();
                        cout << "Lista sasiedztwa: " << endl;
                        graph->MSTPrimAdjList(vert);
                        graph->printMST();
                    } else cout << "Graf jest niespojny!" << endl;
                }
                else cout << "Graf nie zostal zaladowany." << endl;
                break;
        }
        system("PAUSE");
    }while (choice != '0');
}

void menu1FileRead(FileData* fileData, GraphImpl*& graph){

    graph = new GraphImpl(fileData->getVerticesNumber(), fileData->getEdgesNumber());
    edge* data = fileData->getEdges();
    for (int i = 0; i < fileData->getEdgesNumber(); i++) {
        edge edgeData = data[i];
        graph->addEdge(edgeData.tail, edgeData.head, edgeData.cost); //lepiej strukture tu zrobic, chociaz nwm bo wtedy bedzie private
    }
}

void menu2(){
    char choice;

    do{
        cout << "WYZNACZANIE NAJKROTSZEJ SCIEZKI W GRAFIE - MENU:\n"
                "1. Wczytanie grafu z pliku,\n"
                "2. Wyświetlenie grafu macierzowo i listowo,\n"
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
            case '2':       //wyswietlenie grafu
            case '3':       //algorytm 1
            case '4':       //algorytm 2
                break;


        }
    }while (choice != '0');
}

void menu3(){
    char choice;

    do{
        cout << "WYZNACZANIE MAKSYMALNEGO PRZEPLYWU - MENU:\n"
                "1. Wczytanie grafu z pliku,\n"
                "2. Wyświetlenie grafu macierzowo i listowo,\n"
                "3. Algorytm Forda-Fulkersona macierzowo i listowo z wyswietleniem wynikow,\n"
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
            case '2':       //wyswietlenie grafu
            case '3':       //algorytm 1
                break;


        }
    }while (choice != '0');
}
