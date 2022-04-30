#ifndef CHEMPARSE_EQUATION_HPP
#define CHEMPARSE_EQUATION_HPP

#include <vector>

#include "Compound.hpp"
#include "Element.hpp"

namespace chemparse {
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
} // namespace chemparse

#endif
