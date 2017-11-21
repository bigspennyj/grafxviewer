#include "modelview.h"
#include <iostream>

void ModelView::redraw(const DrawingContext& c)
{
    //draw a darkbackground
    c.setColor(0x18, 0x13, 0x1B, 0xff);
    c.drawRectangle(0, 0, width, height);

    Matrix coords = model.getCurrentCoords();
    coords *= projectionMatrix;

    c.setColor(0xD8, 0xD8, 0xD8, 0xff);
    //draw our lines
    for (auto& seg : model.getLineSegments()) {
        auto& p1 = coords[seg.first - 1];
        auto& p2 = coords[seg.second - 1];

        c.drawLine(p1.getX(), p1.getY(), p2.getX(), p2.getY());
    }

    //draw points of our shape
    for (auto& row : coords.getRows()) {
        // draw a 3x3 block around each coordinate
        int x = row.getX() - 1;
        int y = row.getY() - 1;
        c.drawRectangle(x, y, 3, 3);
    }

    c.drawComponent(*this);
}

TransformationMatrix ModelView::computeProjectionMatrix()
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
    double widthTranslation = (width / 2.0);
    double heightTranslation = (height / 2.0);
    
    // so to get the whole thing, we do some stuff
    TransformationMatrix m{
        {unit, 0, 0, 0},
        {0, -unit, 0, 0},
        {0, 0, unit, 0},
        {widthTranslation, heightTranslation, widthTranslation, 1}
    };

    return m;
}
