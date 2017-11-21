#include "catch.hpp"
#include <iostream>

#include "../src/matrix.h"

TEST_CASE("We can multiply a matrix by a matrix", "[matrix]") {
    Matrix m1;

    m1.addRow({1, 2, 3});
    m1.addRow({4, 3, 2});

    SECTION("operator== works") {
        Matrix ref(m1);

        REQUIRE((m1 == ref));
    }

    SECTION("multipying a matrix by a translation matrix works") {
        TransformationMatrix m2;
        m2.addTranslation(-2, 1, 4);

        std::cout << "M1 PRE" << std::endl;
        std::cout << m1 << std::endl;
        std::cout << "M2 PRE" << std::endl;
        std::cout << m2 << std::endl;

        m1 *= m2;

        std::cout << "M1" << std::endl;
        std::cout << m1 << std::endl;
        std::cout << "M2" << std::endl;
        std::cout << m2 << std::endl;

        Matrix comp;
        comp.addRow({-1, 3, 7});
        comp.addRow({2, 4, 6});

        REQUIRE((m1 == comp));
    }
}
