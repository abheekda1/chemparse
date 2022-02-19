#include <iostream>
#include <vector>
#include <string>

namespace chemparse {
    class Element {
    public:
        std::string symbol;
        std::string name;
        double molarMass;
        double atomicMass;
        int atomicNumber;
        std::string discoverer;
        std::string appearance;
        long amount;
    };

    class Compound {
    public:
        explicit Compound(std::vector<Element> elements);
        double getMolarMass();
    private:
        std::vector<Element> elements;
    };

    std::vector<Element> parseFormulaToElements(std::string chemFormula);

    bool populateElement(Element &element);
}// namespace chemparse