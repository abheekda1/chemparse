#include "chemparse.h"

using namespace std;
using namespace chemparse;

bool checkCapitalCase(char currentChar) {
    if (toupper(currentChar) == currentChar) {
        return true;
    }
    return false;
}

namespace chemparse {
    vector<Element> parseFormulaToElements(string chemFormula) {
        vector<Element> elements;

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
                                string amtString;
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

                        // Increment i to skip next char since it's part of this element (just speeds it up a bit -- not necessary)
                        i++;
                    } else {
                        string amtString;
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
                            string amtString;
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
                elements.push_back(element);
            }
        }
        return elements;
    }
}