#include "chemparse.h"
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
    for (const chemparse::Element& element : elements) {
        long amount = element.amount;
        std::string symbol = element.symbol;
        std::string isOrAre;
        isOrAre = (amount == 1 ? "is" : "are");
        std::cout << "There " << isOrAre << " " << amount << " of " << symbol << std::endl;
    }

    waitForExit();
}