#include <iostream>
#include <string>
#include <vector>

namespace chemparse {
struct Element {
  std::string symbol;
  std::string name;
  double molarMass;
  double atomicMass;
  int atomicNumber;
  std::string discoverer;
  std::string appearance;
  long amount;
};

class Compound {
public:
  Compound(std::vector<Element> elements, int amount = 1);

  double getMolarMass();

  inline std::vector<Element> getElements() const { return elements; };
  inline int getAmount() const { return amount; };
private:
  std::vector<Element> elements;
  int amount;
};

class Equation {
public:
  // constructs and destructors
  Equation(std::vector<Compound> reactants, std::vector<Compound> products);

  // member functions
  std::pair<std::vector<int>, std::vector<int>> balanceEquation();
private:
  std::vector<Compound> reactants;
  std::vector<Compound> products;
};

std::vector<Element> parseFormulaToElements(std::string chemFormula);
std::vector<Compound> parseFormulaToCompounds(std::string chemFormula);
Compound combineCompounds(std::vector<Compound> compounds);

bool populateElement(Element &element);
} // namespace chemparse

