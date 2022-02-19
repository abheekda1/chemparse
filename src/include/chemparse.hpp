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

    void populateElement(Element &element);
}// namespace chemparse