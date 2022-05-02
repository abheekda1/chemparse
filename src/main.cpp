#include <iostream>
#include <vector>
#include <csignal>

#include "chemparse/chemparse.hpp"
#include "chemparse/util/rang.hpp"

void signalHandler(int signum) {
  switch (signum) {
  case SIGINT:
    std::cout << "\nExiting..." << std::endl;
    exit(2);
    break;
  case SIGTERM:
    std::cout << "\nExiting..." << std::endl;
    exit(0);
  }
}

int main() {
  signal(SIGINT, signalHandler);
  signal(SIGTERM, signalHandler);

  while (true) {
    std::cout << "> ";

    std::string chemFormula;
    std::cin >> chemFormula;

    if (chemFormula == "exit") {
      raise(SIGTERM);
    }

    std::vector<chemparse::Compound> compounds =
        chemparse::parseFormulaToCompounds(chemFormula);
    if (compounds.empty()) {
      std::cout << "Invalid or empty formula." << std::endl;
      continue;
    }

    const std::vector<chemparse::Element> elements =
        chemparse::combineCompounds(compounds).getElements();
    if (elements.size() == 1) {
      chemparse::Element element = elements[0];
      std::cout << element.name << " (" << element.symbol << ")"
                << ": " << '\n'
                << "Atomic Number: " << element.atomicNumber << '\n'
                << "Atomic Mass: " << element.atomicMass << " amu" << '\n'
                << "Molar Mass: " << element.molarMass << " g/mol" << '\n'
                << "Discoverer: " << element.discoverer << '\n'
                << "Appearance: " << element.appearance << '\n'
                << '\n'
                << "(HINT: 0 or empty values mean unknown or simply not in "
                   "this database)"
                << std::endl;
    } else {
      for (const chemparse::Element &element : elements) {
        long amount = element.amount;
        std::string symbol = element.symbol;
        std::string name = element.name;
        std::string isOrAre = (amount == 1 ? "is" : "are");
        std::cout << "There " << isOrAre << " " << amount << " " << name << " ("
                  << symbol << ")" << std::endl;
      }

      chemparse::Compound compound(elements);
      compound.getMolarMass();
      std::cout << "\nThe total molar mass is: " << compound.getMolarMass()
                << " g/mol\n"
                << "The total atomic mass is: " << compound.getMolarMass()
                << " amu" << std::endl;
    }
  }
}
