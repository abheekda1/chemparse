#include <vector>

#include <chemparse/util/json.hpp>
#include <chemparse/util/periodictable.hpp>

#include "chemparse/chemparse.hpp"

bool checkCapitalCase(char currentChar) {
  return toupper(currentChar) == currentChar;
}

std::vector<std::string> splitString(const std::string &s, const char &c) {
  std::vector<std::string> ret;
  std::string temp;
  for (int i = 0; i < s.length(); i++) {
    if (s.at(i) == c) {
      ret.push_back(temp);
      temp.clear();
      continue;
    }

    temp += s.at(i);
  }
  ret.push_back(temp);
  return ret;
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

std::vector<Compound> parseFormulaToCompounds(std::string chemFormula) {
  std::vector<Compound> compounds;
  for (const auto& chunk : splitString(chemFormula, '(')) {
    if (chunk.empty())
      continue;
    if (chunk.find(')') != std::string::npos) {
      std::vector<std::string> splitFormula = splitString(chunk, ')');
      std::string subFormula = splitFormula.at(0);
      std::string amtString;
      int amount = 0;
      int numdigits = 0;
      if (isdigit(splitFormula.at(1)[0])) {
        while (isdigit(splitFormula.at(1)[numdigits])) {
          amtString += splitFormula.at(1)[numdigits];
          numdigits++;
        }
        splitFormula.at(1).erase(0, numdigits);
        amount = std::stol(amtString);
      } else {
        amount = 1;
      }
      // add the subformula and the next one to the compound vector
      if (compounds.emplace_back(Compound(parseFormulaToElements(subFormula), amount)).getElements().empty())
        return {}; // error because one of the elements failed to be parsed
      if (compounds.emplace_back(Compound(parseFormulaToElements(splitFormula.at(1)), 1)).getElements().empty())
        return {}; 
    } else {
      return {}; // equivalent of an error -- there must be a closing parenthesis for every opening one
    }
  }
  return compounds;
}

bool populateElement(Element &element) {
  std::string symbol = element.symbol;

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

Compound combineCompounds(std::vector<Compound> compounds) {
  std::vector<Element> v;
  size_t amtToReserve = 0;

  for (const auto &c : compounds)
    amtToReserve += v.size() + c.getElements().size();
  
  for (const auto &c : compounds) {
    for (const auto &e : c.getElements()) {
      Element temp = e;
      temp.amount *= c.getAmount(); // multiply the amount of the element by the amount of the compound
      v.push_back(temp);
    }
  }

  // return the compound as just a list of elements
  return Compound(v);
}
} // namespace chemparse

