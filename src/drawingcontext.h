#ifndef DRAWING_CONTEXT_H
#define DRAWING_CONTEXT_H

#include "io.h"

class Component;

class DrawingContext {
public:
    DrawingContext(SDL_IO& io_, SDL_IO::RendererPointer r)
        : io(io_), renderer(std::move(r)) {}

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

    void drawLine(int x1, int y1, int x2, int y2) const
    {
        io.drawLine(x1, y1, x2, y2);
    }

    void setTarget(Component& c)
    {
        renderer.reset(io.createSoftwareRenderer(c).release());
    }

private:
    SDL_IO& io;
    SDL_IO::RendererPointer renderer;
};

#endif // DRAWING_CONTEXT_H
