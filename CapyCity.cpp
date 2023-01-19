#include <iostream>
#include <string>
#include <regex>
#include <vector>
using namespace std;

int length;
int width;
regex menuCheck("[1-4]");
regex numberCheck("[[:digit:]]+");

void menu();

class Building {
public:
    Building() {
        basePrice = 0;
        label = '0';
    }

    Building(
        int basePrice, char label) :basePrice(basePrice), label(label) {}

    int getPrice() const {
        return basePrice;
    }

    char getLabel() const {
        return label;
    }

protected:
    int basePrice;
    char label;
    string name;
};

class Material {
public:
    Material(string name, int price) : name(name), price(price) {}
    string getName() const {
        return name;
    }
    int getPrice() const {
        return price;
    }
private:
    string name;
    int price;
};

class Wood : public Material {
public:
    Wood() : Material("Holz", 25) {}
};

class Metal : public Material {
public:
    Metal() : Material("Metall", 15) {}
};

class Plastic : public Material {
public:
    Plastic() : Material("Kunststoff", 5) {}
};

class WaterPlant : public Building {
public:
    WaterPlant() : Building(100, 'W') {
        materials = vector<Material>() = {
            Wood(),
            Wood(),
            Metal(),
            Metal() };
    }
    vector<Material> materials;
};

class WindPlant : public Building {
public:
    WindPlant() : Building(50, 'I') {
        materials = vector<Material>() = {
            Plastic(),
            Plastic(),
            Metal(),
            Metal() };
    }
    vector<Material> materials;
};

class SolarPlant : public Building {
public:
    SolarPlant() : Building(250, 'S') {
        materials = vector<Material>() = {
            Plastic(),
            Plastic(),
            Plastic(),
            Metal() };
    }
    vector<Material> materials;
};

Building* buildingMenu();

Building*** Area;

int main(int argc, char** argv) {

    length = stoi(argv[1]);
    width = stoi(argv[2]);

    cout << "Herzlich Willkommen in CapyCity!\n";

    Area = new Building * *[length];
    for (int x = 0; x < length; x++) {
        Area[x] = new Building * [width];
        for (int y = 0; y < length; y++) {
            Area[x][y] = nullptr;
        }
    }

    while (true) {
        menu();
    }
}

class CapycitySim {
public:
    void buildBuilding() {
        Building* buildingChoice = buildingMenu();

        if (buildingChoice == nullptr) {
            return;
        }

        int startX{ positionX() };
        int startY{ positionY() };
        int breite{ buildingWidth() };
        int laenge{ buildingLength() };

        for (int i = startX; i < startX + breite; i++) {
            for (int j = startY; j < startY + laenge; j++) {
                if ((startX + breite) > width || (startY + laenge) > length || Area[j][i] != nullptr) {
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
        if (regex_match(startX, numberCheck) && stoi(startX) < length) {
            return stoi(startX);
        }
        else {
            cout << "Ziffer zwischen 0 und " << (length - 1) << " eingeben\n";
            return positionX();
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
            return positionY();
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
            cout << "Die Breite muss eine Ziffer zwischen 1 und " << width << " sein!\n";
            return buildingWidth();
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
            return buildingLength();
        }
    }

    void buildingPlan() {
        int w = 0;
        int i = 0;
        int s = 0;

        for (int x = 0; x < length; x++) {
            for (int y = 0; y < width; y++) {
                if (Area[x][y] == nullptr) {
                    cout << "[ ]";
                }
                else {
                    cout << "[" << Area[x][y]->getLabel() << "]";

                    if (Area[x][y]->getLabel() == 'W') {
                        w++;
                    }
                    if (Area[x][y]->getLabel() == 'I') {
                        i++;
                    }
                    if (Area[x][y]->getLabel() == 'S') {
                        s++;
                    }
                }
            }
            cout << endl;
        }

        int mat = 0;
        int mat2 = 0;
        int matCost = 0;
        for (int count = 0; count < w; count++) {
            for (auto& i : WaterPlant().materials) {
                if (i.getName() == "Holz") {
                    mat++;
                    matCost += Wood().getPrice();
                }
                if (i.getName() == "Metall") {
                    mat2++;
                    matCost += Metal().getPrice();
                }
            }
        }
        cout
            << endl << w << " Wasserkraftwerke\n"
            << "Ein Wasserkraftwerk kostet: " << WaterPlant().getPrice() << "$\n"
            << "Wasserkraftwerke benötigen " << mat << " Holz und " << mat2 << " Metall\n"
            << "Gesamtkosten der Wasserkraftwerke betragen: " << (w * WaterPlant().getPrice()) + matCost << "$\n";

        int allCost = 0;
        allCost += (w * WaterPlant().getPrice()) + matCost;

        mat = 0;
        mat2 = 0;
        matCost = 0;
        for (int count = 0; count < i; count++) {
            for (auto& i : WindPlant().materials) {
                if (i.getName() == "Kunststoff") {
                    mat++;
                    matCost += Plastic().getPrice();
                }
                if (i.getName() == "Metall") {
                    mat2++;
                    matCost += Metal().getPrice();
                }
            }
        }
        cout
            << endl << i << " Windkraftwerke\n"
            << "Ein Windkraftwerk kostet: " << WindPlant().getPrice() << "$\n"
            << "Wasserkraftwerke benötigen " << mat << " Kunststoff und " << mat2 << " Metall\n"
            << "Gesamtkosten der Windkraftwerke betragen: " << (i * WindPlant().getPrice()) + matCost << "$\n";

        allCost += (i * WindPlant().getPrice()) + matCost;

        mat = 0;
        mat2 = 0;
        matCost = 0;
        for (int count = 0; count < s; count++) {
            for (auto& i : SolarPlant().materials) {
                if (i.getName() == "Kunststoff") {
                    mat++;
                    matCost += Plastic().getPrice();
                }
                if (i.getName() == "Metall") {
                    mat2++;
                    matCost += Metal().getPrice();
                }
            }
        }
        cout
            << endl << s << " Solarpanele\n"
            << "Ein Solarpanel kostet: " << SolarPlant().getPrice() << "$\n"
            << "Solarpanel benötigt " << mat << " Kunststoff und " << mat2 << " Metall\n"
            << "Gesamtkosten der Solarpanele betragen: " << (s * SolarPlant().getPrice()) + matCost << "$\n";

        allCost += (s * SolarPlant().getPrice()) + matCost;
        cout << endl << "Gesamtkosten: " << allCost << "$\n";

        menu();
    }

    void deleteArea() {
        int startX{ positionX() };
        int startY{ positionY() };
        int breite{ buildingWidth() };
        int laenge{ buildingLength() };

        for (int i = startX; i < min(width, startX + breite); i++) {
            for (int j = startY; j < min(length, startY + laenge); j++) {
                Area[j][i] = nullptr;
            }
        }
        menu();
    }
};

void menu() {
    string choice;

    CapycitySim CapycitySim;

    cout << endl
        << "1 - Setzen eines Gebaeudes\n"
        << "2 - Einen Bereich loeschen\n"
        << "3 - Aktuellen Bauplan anzeigen\n"
        << "4 - Verlassen\n";

    cin >> choice;

    if (regex_match(choice, menuCheck)) {
        switch (stoi(choice)) {
        case 1:
            //Gebäude setzen    
            CapycitySim.buildBuilding();
            break;
        case 2:
            //Bereich löschen
            CapycitySim.deleteArea();
            break;
        case 3:
            //Print Blauplan
            CapycitySim.buildingPlan();
            break;

        case 4:
            //Beenden des Programms
            cout << "Auf wiedersehen";
            exit(0);
        }
    }
    else {
        cout << "Nur Ziffern von 1 - 4 erlaubt!\n";
        menu();
    }
}

Building* buildingMenu() {
    string buildingChoice;

    cout << "Welches Gebaeude soll gebaut werden?";

    cout << endl
        << "1 - Wasserkraftwerk\n"
        << "2 - Windkraftwerk\n"
        << "3 - Solarpanel\n"
        << "4 - Zum Hauptmenue zurueckkehren\n";
    cin >> buildingChoice;

    if (regex_match(buildingChoice, menuCheck)) {
        switch (stoi(buildingChoice)) {
        case 1:
            return new WaterPlant();
            break;
        case 2:
            return new WindPlant();
            break;
        case 3:
            return new SolarPlant();
            break;
        default:
            return nullptr;
        }
    }
    else {
        cout << "Nur Ziffern von 1 - 4 erlaubt!\n";
        return buildingMenu();
    }
}