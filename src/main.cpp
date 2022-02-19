#include "chemparse.hpp"
#include <climits>

void waitForExit() {
    std::cout << std::endl;
    std::cout << "PLEASE PRESS ENTER OR CLOSE THE WINDOW TO TERMINATE THE PROGRAM:" << std::endl;
    std::cin.clear(); std::cin.ignore(INT_MAX, '\n');
    std::cin.get();
}

int main() {
    std::cout << "Please enter the formula:" << std::endl;

    std::string chemFormula; std::cin >> chemFormula;
    std::vector<chemparse::Element> elements = chemparse::parseFormulaToElements(chemFormula);

    std::cout << std::endl;
    for (chemparse::Element& element : elements) {
        chemparse::populateElement(element);
        long amount = element.amount;
        std::string symbol = element.symbol;
        std::string name = element.name;
        std::string isOrAre = (amount == 1 ? "is" : "are");
        std::cout << "There " << isOrAre << " " << amount << " " << name << " (" << symbol << ")" << std::endl;
    }

    waitForExit();
}