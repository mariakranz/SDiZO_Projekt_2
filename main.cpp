#include <iostream>
#include "data/FileData.h"
#include "interfaces/ShortestPathMenu.h"
#include "interfaces/MSTMenu.h"

using namespace std;

void menu();
void menu3();

int main() {
    menu();
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
                menu1->menu();
                break;
            case '2':
                menu2->menu();
                break;
            case '3':
                menu3();
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
