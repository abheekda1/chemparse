#ifndef CHEMPARSE_COMPOUND_HPP
#define CHEMPARSE_COMPOUND_HPP

#include <vector>

#include "Element.hpp"

namespace chemparse {
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
} // namespace chemparse

#endif
