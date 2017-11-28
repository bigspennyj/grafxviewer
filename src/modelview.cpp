#include "modelview.h"
#include <iostream>

void ModelView::redraw(const DrawingContext& c)
{
    //draw a darkbackground
    c.setColor(0x18, 0x13, 0x1B, 0xff);
    c.drawRectangle(0, 0, width, height);

    auto projectionMatrix = computeProjectionMatrix();
    auto coords = model.getCurrentCoords();
    for (auto& coord : coords)
        coord *= projectionMatrix;

    //draw our lines
    for (auto& seg : model.getLineSegments()) {
        auto& p1 = coords[seg.first - 1];
        auto& p2 = coords[seg.second - 1];

        if (p1.z < 0 && p2.z < 0) {
            c.setColor(0x74, 0x74, 0x74, 0xff);
        } else {
            c.setColor(0xD8, 0xD8, 0xD8, 0xff);
        }

        c.drawLine(p1.x, p1.y, p2.x, p2.y);
    }

    c.setColor(0xD8, 0xD8, 0xD8, 0xff);
    //draw points of our shape
    for (auto& row : coords) {
        // draw a 3x3 block around each coordinate
        int x = row.x - 1;
        int y = row.y - 1;
        c.drawRectangle(x, y, 3, 3);
    }

    c.drawComponent(*this);
}

TransformationMatrix<double> ModelView::computeProjectionMatrix()
{
    /*
    Vector3D ourPosition(0, 0, -100);

    //i think this stuff is all right?
    Vector3D nHat(0, 0, -1);

    // up should just be 0 1 0, right?
    Vector3D uHat(0, 1, 0);

    // and vHat is just going to be 1 0 1 right?
    Vector3D vHat(1, 0, 0);
    */
    double widthTranslation = (width / 2.0) - (model.getOriginalCenter().x * unit);
    double heightTranslation = (height / 2.0) + (model.getOriginalCenter().y * unit);

    // so to get the whole thing, we do some stuff
    std::array<std::array<double, 4>, 4> m{{
        {{unit, 0, 0, 0}},
        {{0, -unit, 0, 0}},
        {{0, 0, unit, 0}},
        {{widthTranslation, heightTranslation, 0, 1}}
    }};

    return TransformationMatrix<double>(m);
}
