#ifndef CHEMPARSE_CHEMPARSE_HPP
#define CHEMPARSE_CHEMPARSE_HPP

#include <iostream>
#include <string>
#include <vector>

#include "Compound.hpp"
#include "Element.hpp"
#include "Equation.hpp"

namespace chemparse {
std::vector<Element> parseFormulaToElements(std::string chemFormula);
std::vector<Compound> parseFormulaToCompounds(std::string chemFormula);
Compound combineCompounds(std::vector<Compound> compounds);

bool populateElement(Element &element);
} // namespace chemparse

#endif
