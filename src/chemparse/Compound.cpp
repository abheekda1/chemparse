#include <vector>

#include "chemparse/Compound.hpp"

namespace chemparse {
Compound::Compound(std::vector<Element> elmnts, int amt)
    : elements(elmnts), amount(amt) {}

double Compound::getMolarMass() {
  double molarMass = 0.0;
  for (const chemparse::Element &element : elements) {
    molarMass += static_cast<double>(element.amount) * element.molarMass;
  }
  return molarMass;
}
} // namespace chemparse