#ifndef CHEMPARSE_ELEMENT_HPP
#define CHEMPARSE_ELEMENT_HPP

#include <string>

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
} // namespace chemparse

#endif
