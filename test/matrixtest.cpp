#include "catch.hpp"

#include "matrix.h"

TEST_CASE("We can multiply a matrix by a matrix", "[MULT]") {
    Matrix m1;
    TransformationMatrix m2;

    m1.addRow({1, 2, 3, 4});
    m1.addRow({4, 3, 2, 1});

    Matrix ref(m1);

    m1 *= m2;
    
    REQUIRE(m1 == ref);

}
