#include <fstream>

#include "chemparse.hpp"
#include "json.hpp"
#include "periodictable.hpp"

bool checkCapitalCase(char currentChar) {
  if (toupper(currentChar) == currentChar) {
    return true;
  }
  return false;
}

namespace chemparse {
std::vector<Element> parseFormulaToElements(std::string chemFormula) {
  std::vector<Element> elements;

  for (int i = 0; i < chemFormula.size(); i++) {
    char currentChar = chemFormula[i];
    char nextChar = chemFormula[i + 1];

    Element element;

    // Make sure the current character is capital to prevent starting with a
    // lowercase letter
    if (checkCapitalCase(currentChar)) {
      // If current character is capital and the next one isn't, they're one
      // element
      if (!checkCapitalCase(nextChar) && i < chemFormula.size() - 1) {
        if (!isdigit(nextChar)) {
          element.symbol = currentChar;
          element.symbol += nextChar;

          // Make sure it's less than two less the length of the array to
          // prevent accessing something outside
          if (i < chemFormula.size() - 2) {
            if (isdigit(chemFormula[i + 2])) {
              std::string amtString;
              int numLength = 0;
              for (int j = i + 2; j < chemFormula.size(); j++) {
                if (isdigit(chemFormula[j])) {
                  amtString += chemFormula[j];
                  numLength++;
                } else {
                  break;
                }
              }
              element.amount = stol(amtString);
              i += numLength;
            } else {
              element.amount = 1;
            }
          } else {
            element.amount = 1;
          }

          // Increment i to skip next char since it's part of this element (just
          // speeds it up a bit -- not necessary)
          i++;
        } else {
          std::string amtString;
          int numLength = 0;
          for (int j = i + 1; j < chemFormula.size(); j++) {
            if (isdigit(chemFormula[j])) {
              amtString += chemFormula[j];
              numLength++;
            } else {
              break;
            }
          }
          element.amount = stol(amtString);
          i += numLength;
        }
        // Otherwise, this one is its own element
      } else {
        element.symbol = currentChar;

        // Make sure it's less than two less the length of the array to prevent
        // accessing something outside
        if (i < chemFormula.size() - 1) {
          if (isdigit(chemFormula[i + 1])) {
            std::string amtString;
            int numLength = 0;
            for (int j = i + 1; j < chemFormula.size(); j++) {
              if (isdigit(chemFormula[j])) {
                amtString += chemFormula[j];
                numLength++;
              } else {
                break;
              }
            }
            element.amount = stol(amtString);
            i += numLength;
          } else {
            element.amount = 1;
          }
        } else {
          element.amount = 1;
        }
      }
      bool foundElement = populateElement(element);
      if (!foundElement) {
        elements.clear();
        break;
      } else {
        elements.push_back(element);
      }
    }
  }
  return elements;
}

bool populateElement(Element &element) {
  std::string symbol = element.symbol;

  std::ifstream f("periodic-table.json");
  std::string periodicTableData(reinterpret_cast<char *>(periodic_table));

  nlohmann::json elementData =
      nlohmann::json::parse(periodicTableData)["elements"];
  bool foundElement = false;
  for (int i = 0; i < elementData.size(); i++) {
    if (elementData[i]["symbol"] == symbol) {
      nlohmann::json currentElementData = elementData[i];
      element.name = currentElementData.value("name", "");
      element.molarMass = currentElementData.value("atomic_number", 0);
      element.atomicMass = currentElementData.value("atomic_mass", 0.0);
      element.molarMass = currentElementData.value("atomic_mass", 0.0);
      element.atomicNumber = currentElementData.value("number", 0);
      element.appearance = currentElementData.value("appearance", "");
      element.discoverer = currentElementData.value("discovered_by", "");
      foundElement = true;
      break;
    }
  }
  return foundElement;
}

Compound::Compound(std::vector<Element> elmnts) : elements(elmnts) {}

double Compound::getMolarMass() {
  double molarMass = 0.0;
  for (chemparse::Element element : elements) {
    molarMass += double(element.amount) * element.molarMass;
  }
  return molarMass;
}
} // namespace chemparse
