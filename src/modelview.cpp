#include "modelview.h"

void ModelView::redraw(const DrawingContext& c)
{
    //draw a black background
    c.setColor(0xff000000);
    c.drawRectangle(surface, 0, 0, width, height);
    auto& coords = model.getCurrentCoords();

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
    c.setColor(0xffffffff);
    for (auto& row : coords.getRows()) {
        // draw a 3x3 block around each coordinate
        int x = ((row.getX() * unit) + width / 2) - 1;
        int y = ((row.getY() * unit) + height / 2) - 1;
        c.drawRectangle(surface, x, y, 3, 3);
    }

    c.drawComponent(*this);
    // always redraw?
    needUpdate = false;
}
