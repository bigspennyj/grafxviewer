#include "catch.hpp"
#include "../src/matrix.h"

TEST_CASE("Transformation Matricies should function properly", "[transformation]")
{
    TransformationMatrix transformationMatrix;
    
    SECTION("should be able to add translation")
    {
        transformationMatrix.addTranslation(15, -2, 4);

        TransformationMatrix result({
            {1, 0, 0, 0},
            {0, 1, 0, 0},
            {0, 0, 1, 0},
            {15, -2, 4, 1}
        });

        REQUIRE((transformationMatrix == result));
    }

    SECTION("Should be able to add a rotation")
    {
        // add a 10 degree rotation clockwise around X
        transformationMatrix.addRotation({10, 0, 0, 0});

        TransformationMatrix result;

        REQUIRE(false);
    }
    
}
