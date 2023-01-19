#include <iostream>
#include <string>
#include <regex>
using namespace std;

void menu();
enum building { Empty = 0, Water = 1, Wind = 2, Solar = 3 };
void buildingPlan();
void deleteArea();
void buildBuilding();
int positionX();
int positionY();
int buildingWidth();
int buildingLength();

int length;
int width;
regex menuCheck("[1-4]");
regex numberCheck("[[:digit:]]+");

building** Area;

int main(int argc, char **argv) {
    
    length = stoi(argv[1]);
    width = stoi(argv[2]);

    cout << "Herzlich Willkommen in CapyCity!\n";

    Area = new building * [length];
    for (int x = 0; x < length; x++) {
        Area[x] = new building[width];
        for (int y = 0; y < length; y++) {
            Area[x][y] = building::Empty;
        }
    }

    while (true) {
        menu();
    }
}

void menu(){
    string choice;

    cout << endl
        << "1 - Setzen eines Gebaeudes\n"
        << "2 - Einen Bereich loeschen\n"
        << "3 - Aktuellen Bauplan anzeigen\n"
        << "4 - Verlassen\n";

    cin >> choice;

    if (regex_match(choice, menuCheck)) {
        switch (stoi(choice)) {
        case 1:
            //Setzen eines Geb�udes   
            buildBuilding();
            break;
        case 2:
            //Bereich l�schen
            deleteArea();
            break;
        case 3:
            //Print Blauplan
            buildingPlan();
            break;

        case 4:
            //Beenden des Programms
            cout << "Auf wiedersehen";
            exit(0);
        }
    }
    else {
        cout << "Nur die Ziffern 1 - 4 erlaubt!\n";
        menu();
    } 
}

building buildingMenu() {
    string buildingChoice;

    cout << "Was fuer ein Gebaeude soll gebaut werden?";

    cout << endl
        << "1 - Wasserkraftwerk\n"
        << "2 - Windkraftwerk\n"
        << "3 - Solarpanel\n"
        << "4 - Zum Hauptmenue zurueckkehren\n";
    cin >> buildingChoice;

    if (regex_match(buildingChoice, menuCheck)) {
        switch (stoi(buildingChoice)) {
        case 1:
            return Water;
            break;
        case 2:
            return Wind;
            break;
        case 3:
            return Solar;
            break;
        case 4:
            menu();
        }
    }
    else {
        cout << "Nur die Ziffern 1 - 4 erlaubt!\n";
        buildingMenu();
    }
}

void buildBuilding() {
    building buildingChoice = buildingMenu();

    int startX{ positionX() };
    int startY{ positionY() };
    int breite{ buildingWidth() };
    int laenge{ buildingLength() };

    for (int i = startX; i < startX + breite; i++) {
        for (int j = startY; j < startY + laenge; j++) {
            if ((startX + breite) > width || (startY + laenge) > length || Area[j][i] != Empty) {
                cout << "Flaeche ist ausserhalb des Baubereichs oder belegt!\n\n";
                return buildBuilding();
            }
            else {
                Area[j][i] = buildingChoice;
            }
        }
    }
}

int positionX() {
    string startX;

    cout << "Position X eingeben: \n";
    cin >> startX;
    if (regex_match(startX, numberCheck) && stoi(startX)<length) {
        return stoi(startX);
    }
    else {
        cout << "Ziffer zwischen 0 und " << (length - 1) << " eingeben\n";
        positionX();
    }
}

int positionY() {
    string startY;

    cout << "Position Y eingeben: \n";
    cin >> startY;
    if (regex_match(startY, numberCheck) && stoi(startY) < width) {
        return stoi(startY);
    }
    else {
        cout << "Ziffer zwischen 0 und " << (width - 1) << " eingeben\n";
        positionY();
    }
}

int buildingWidth() {
    string breite;

    cout << "Breite der Flaeche angeben: \n";
    cin >> breite;
    if (regex_match(breite, numberCheck) && stoi(breite) > 0 && stoi(breite) <= width) {
        return stoi(breite);
    }
    else {
        cout << "Breite muss eine Ziffer zwischen 1 und " << width << " sein!\n";
        buildingWidth();
    }
}

int buildingLength() {
    string laenge;

    cout << "Laenge der Flaeche angeben: \n";
    cin >> laenge;
    if (regex_match(laenge, numberCheck) && stoi(laenge) > 0 && stoi(laenge) <= length) {
        return stoi(laenge);
    }
    else {
        cout << "Die Laenge muss eine Ziffer zwischen 1 und " << length << " sein!\n";
        buildingLength();
    }
}

void buildingPlan() {
    for (int x = 0; x < length; x++) {
        for (int y = 0; y < width; y++) {
            cout << Area[x][y];
        }
        cout << endl;
    }
    menu();
}

void deleteArea() {
    int startX{ positionX() };
    int startY{ positionY() };
    int breite{ buildingWidth() };
    int laenge{ buildingLength() };

    for (int i = startX; i < startX + breite; i++) {
        for (int j = startY; j < startY + laenge; j++) {
            Area[j][i] = Empty;
        }
    }
    menu();
}