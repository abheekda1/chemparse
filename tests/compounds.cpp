#include <catch2/catch_test_macros.hpp>

#include "chemparse/chemparse.hpp"

TEST_CASE("Parse compounds", "[compounds]") {
    SECTION("without parentheses") {
        std::vector<chemparse::Compound> naoh = chemparse::parseFormulaToCompounds("NaOH");
        REQUIRE(naoh.size() == 1);
        for (const auto &c : naoh) {
            REQUIRE(!c.getElements().empty());
        }
    }

    SECTION("with parentheses") {
        std::vector<chemparse::Compound> nh4_2_so4 = chemparse::parseFormulaToCompounds("(NH4)2SO4");
        REQUIRE(nh4_2_so4.size() == 2);
        for (const auto &c : nh4_2_so4) {
            REQUIRE(!c.getElements().empty());
        }
    }

    SECTION("combine compounds") {
        chemparse::Compound c1({
            chemparse::Element({
                "H",
                "Hydrogen",
                1.008,
                1.008,
                1,
                "Henry Cavendish",
                "colorless gas"
            })
        });
        chemparse::Compound c2({
            chemparse::Element({
                "Cl",
                "Chlorine",
                35.45,
                35.45,
                17,
                "Carl Wilhelm Scheele",
                "pale yellow-green gas"
            })
        });
        chemparse::Compound c = chemparse::combineCompounds({c1, c2});
        REQUIRE(c.getElements().size() == 2);
        REQUIRE(c.getElements().at(0).symbol == "H");
        REQUIRE(c.getElements().at(1).symbol == "Cl");
    }
}
