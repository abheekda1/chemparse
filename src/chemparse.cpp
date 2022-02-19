#include "chemparse.hpp"
#include "json.hpp"
#include <fstream>

bool checkCapitalCase(char currentChar) {
    if (toupper(currentChar) == currentChar) {
        return true;
    }
    return false;
}

namespace chemparse {
    std::vector<Element> parseFormulaToElements(std::string chemFormula) {
        std::vector<Element> elements;

        for (int i = 0; i < chemFormula.size(); i ++) {
            char currentChar = chemFormula[i];
            char nextChar = chemFormula[i + 1];

            Element element;

            // Make sure the current character is capital to prevent starting with a lowercase letter
            if (checkCapitalCase(currentChar)) {
                // If current character is capital and the next one isn't, they're one element
                if (!checkCapitalCase(nextChar) && i < chemFormula.size() - 1) {
                    if (!isdigit(nextChar)) {
                        element.symbol = currentChar;
                        element.symbol += nextChar;

                        // Make sure it's less than two less the length of the array to prevent accessing something outside
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

                        // Increment i to skip next char since it's part of this element (just speeds it up a bit -- not necessary)
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

                    // Make sure it's less than two less the length of the array to prevent accessing something outside
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
                            //element.amount = chemFormula[i + 1] - '0' /*convert to int from val stored in char*/;
                            //i++;
                        } else {
                            element.amount = 1;
                        }
                    } else {
                        element.amount = 1;
                    }
                }
                bool foundElement = populateElement(element);
                if (!foundElement) {
                    elements.empty();
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
        long amount = element.amount;

        std::ifstream f("periodic-table.json");
        std::string periodicTableData;

        if (f) {
            std::stringstream ss;
            ss << f.rdbuf();
            periodicTableData = ss.str();
        } else {
            std::cout << "ERROR: Missing the periodic table JSON file!" << std::endl;
            exit(1);
        }

        nlohmann::json elementData = nlohmann::json::parse(periodicTableData)["elements"];
        bool foundElement = false;
        for (int i = 0; i < elementData.size(); i++) {
            if (elementData[i]["symbol"] == symbol) {
                element.name = elementData[i]["name"];
                element.molarMass = double(elementData[i]["atomic_mass"]);
                element.atomicMass = double(elementData[i]["atomic_mass"]);
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
}