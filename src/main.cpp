#include "chemparse.h"
#include <cstdio>
#include <sstream>

struct Element_t {
    int atomicNumber;
    int name;
    int symbol;
    int atomicMass;
    int numProtons;
    int numNeutrons;
    int numElectrons;
};

int main() {
    /*freopen("test.csv", "r", stdin);

    for (int i = 0; i < 118; i++) {
        std::string currentElementRaw; std::cin >> currentElementRaw;
        std::string currentData;
        vector<std::string> currentDataParsed;
        for (int j = 0; j < 7; j++) {
            while (currentElementRaw[j] != ',') {
                currentData += currentElementRaw[j];
            }
            std::stringstream ss(currentData);
            std::cout << currentData;
        }
        std::cout << currentElementRaw << std::endl;
    }*/
    cout << "Please enter the formula:" << endl;

    string chemFormula; cin >> chemFormula;
    vector<chemparse::Element> elements = chemparse::parseFormulaToElements(chemFormula);

    cout << endl;
    for (int i = 0; i < elements.size(); i++) {
        int amount;
        string symbol;
        cout << "There are " << elements[i].amount << " " << elements[i].symbol << endl;
    }

    cout << "PLEASE PRESS ENTER OR CLOSE THE WINDOW TO TERMINATE THE PROGRAM:" << endl;
    std::cin.clear(); std::cin.ignore(INT_MAX, '\n');
    std::cin.get();
}