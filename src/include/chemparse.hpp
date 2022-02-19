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

    class Compound {
    public:
        std::vector<Element> elements;
        virtual long getMolarMass() = 0;
    };

    std::vector<Element> parseFormulaToElements(std::string chemFormula);

    void populateElement(Element &element);
}// namespace chemparse