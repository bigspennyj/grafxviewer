#include "catch.hpp"

#include "../src/matrix.h"

TEST_CASE("We can multiply a matrix by a matrix", "[matrix]") {
    Matrix m1;

    m1.addRow({1, 2, 3, 4});
    m1.addRow({4, 3, 2, 1});

    SECTION("operator== works") {
        Matrix ref(m1);

        REQUIRE((m1 == ref));
    }

    SECTION("multipying a matrix by a translation matrix works") {
        TransformationMatrix m2;
        m2.addTranslation(-2, 1);
        m1 *= m2;

        Matrix comp;
        comp.addRow({-1, 3, 3, 4});
        comp.addRow({2, 4, 2, 1});

        REQUIRE((m1 == comp));
    }

}
