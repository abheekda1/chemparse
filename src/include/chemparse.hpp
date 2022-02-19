#include <iostream>
#include <vector>
#include <string>

namespace chemparse {
    class Element {
    public:
        std::string symbol;
        std::string name;
        long amount;
    };

    std::vector<Element> parseFormulaToElements(std::string chemFormula);
} // namespace chemparse