#include <iostream>
#include "data/FileData.h"
#include "interfaces/ShortestPathMenu.h"
#include "interfaces/MSTMenu.h"
#include "data/TimeTests.h"

using namespace std;

void menu();
void tests();

int main() {
    menu();
    //tests();
    return 0;
}

void menu(){
    ShortestPathMenu* menu2 = new ShortestPathMenu();
    MSTMenu* menu1 = new MSTMenu();
    char choice;

    do{
        cout << "\n----MENU----\n"
                "1. Wyznaczanie minimalnego drzewa rozpinajacego (MST).\n"
                "2. Wyznaczanie najkrotszej sciezki w grafie.\n"
                "0. Wyjdz z programu.\n"
                "Wprowdz numer: ";
        cin >> choice;
        switch (choice) {
            default:
                cout << "Nie ma takiej opcji!\n";
                break;
            case '0': break;
            case '1':
                menu1->menu();
                break;
            case '2':
                menu2->menu();
                break;
        }
    }while (choice != '0');
}

void tests(){
    TimeTests* test = new TimeTests();
    test->testKruskalMatrix();
    test->testKruskalList();
    test->testPrimMatrix();
    test->testPrimList();

    test->testDijkstraMatrix();
    test->testDijkstraList();
    test->testBellmanFordMatrix();
    test->testBellmanFordList();


}
