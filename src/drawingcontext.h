#ifndef DRAWING_CONTEXT_H
#define DRAWING_CONTEXT_H

#include "io.h"

class DrawingContext {
public:
    DrawingContext(SDL_IO& io_) : io(io_) {}

    DrawingContext(DrawingContext&) = delete;
    DrawingContext operator=(DrawingContext&) = delete;

    void drawRectangle(const SDL_IO::SurfacePointer& s, int x1, int y1, int x2, int y2) const
    {
        io.drawRectangle(s, x1, y1, x2, y2);
    }
    void drawComponent(const Component& c) const
    {
        io.drawComponent(c);
    }
    void setColor(int rgba) const
    {
        io.setColor(rgba);
    }
private:
    SDL_IO& io;
};

#endif // DRAWING_CONTEXT_H
