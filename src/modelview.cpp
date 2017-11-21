#include "modelview.h"

void ModelView::redraw(const DrawingContext& c)
{
    //draw a darkbackground
    c.setColor(0x18, 0x13, 0x1B, 0xff);
    c.drawRectangle(0, 0, width, height);

    Matrix coords = model.getCurrentCoords();
    Matrix rcoords = model2.getCurrentCoords();
    //coords *= projectionMatrix;

    c.setColor(0xD8, 0x00, 0x00, 0xff);
    //draw our lines
    for (auto& seg : model.getLineSegments()) {
        auto& p1 = coords[seg.first - 1];
        auto& p2 = coords[seg.second - 1];

        c.drawLine((p1.getX() * unit) + width / 2,
                (p1.getY() * unit) + height / 2,
                (p2.getX() * unit) + width / 2,
                (p2.getY() * unit) + height / 2);
    }

    //draw points of our shape
    for (auto& row : coords.getRows()) {
        // draw a 3x3 block around each coordinate
        int x = ((row.getX() * unit) + width / 2) - 1;
        int y = ((row.getY() * unit) + height / 2) - 1;
        c.drawRectangle(surface, x, y, 3, 3);
    }

    c.setColor(0x00, 0x44, 0xD8, 0xff);
    //draw our lines
    for (auto& seg : model2.getLineSegments()) {
        auto& p1 = rcoords[seg.first - 1];
        auto& p2 = rcoords[seg.second - 1];

        c.drawLine((p1.getX() * unit) + width / 2,
                (p1.getY() * unit) + height / 2,
                (p2.getX() * unit) + width / 2,
                (p2.getY() * unit) + height / 2);
    }

    //draw points of our shape
    for (auto& row : rcoords.getRows()) {
        // draw a 3x3 block around each coordinate
        int x = ((row.getX() * unit) + width / 2) - 1;
        int y = ((row.getY() * unit) + height / 2) - 1;
        c.drawRectangle(surface, x, y, 3, 3);
    }
    c.drawComponent(*this);
}

TransformationMatrix ModelView::computeProjectionMatrix()
{
    Vector3D ourPosition(0, 0, -100);

    //i think this stuff is all right?
    Vector3D nHat(0, 0, -1);

    // up should just be 0 1 0, right?
    Vector3D uHat(0, 1, 0);

    // and vHat is just going to be 1 0 1 right?
    Vector3D vHat(1, 0, 0);
    
    // so to get the whole thing, we do some stuff
    TransformationMatrix m{
        {0, 1, 0, 1},
        {1, 0, 0, 1},
        {0, 0, -1, 1},
        {0, 0, 0, 1}
    };
    
    return m;
}
