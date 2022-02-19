#include "chemparse.hpp"
#include <climits>

void waitForExit() {
    std::cout << std::endl;
    std::cout << "PLEASE PRESS ENTER OR CLOSE THE WINDOW TO TERMINATE THE PROGRAM:" << std::endl;
    std::cin.clear(); std::cin.ignore(INT_MAX, '\n');
    std::cin.get();
}

int main() {
    while (true) {
        std::cout << "> ";

        std::string chemFormula;
        std::cin >> chemFormula;

        if (chemFormula == "exit") {
            std::cout << std::endl << "Exiting..." << std::endl;
            exit(0);
        }

        std::vector<chemparse::Element> elements = chemparse::parseFormulaToElements(chemFormula);
        if (elements.size() == 0) {
            std::cout << "Invalid or empty formula." << std::endl;
            continue;
        } else if (elements.size() == 1) {
            chemparse::Element element = elements[0];
            std::cout << "The element " << element.name << " (" << element.symbol << ")"
                << " appears as a " << element.appearance << " and was discovered by "
                << element.discoverer << "." << std::endl;
        } else {
            for (chemparse::Element &element: elements) {
                long amount = element.amount;
                std::string symbol = element.symbol;
                std::string name = element.name;
                std::string isOrAre = (amount == 1 ? "is" : "are");
                std::cout << "There " << isOrAre << " " << amount << " " << name << " (" << symbol << ")" << std::endl;
            }

            chemparse::Compound compound(elements);
            compound.getMolarMass();
            std::cout << std::endl;
            std::cout << "The total molar mass is: " << compound.getMolarMass() << " g/mol" << std::endl;
            std::cout << "The total atomic mass is: " << compound.getMolarMass() << " amu" << std::endl;
        }
    }
}