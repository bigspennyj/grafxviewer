#ifndef DRAWING_CONTEXT_H
#define DRAWING_CONTEXT_H

#include "io.h"
#include <iostream>

class Component;

class DrawingContext {
public:
    DrawingContext(SDL_IO& io_, const SDL_IO::RendererPointer& r)
        : io(io_) {}

    DrawingContext(DrawingContext&) = delete;
    DrawingContext operator=(DrawingContext&) = delete;

    void drawRectangle(int x1, int y1, int x2, int y2) const
    {
        io.drawRectangle(x1, y1, x2, y2);
    }

    void drawComponent(const Component& c) const
    {
        io.drawComponent(c);
    }

    void setColor(int r, int g, int b, int a) const
    {
        io.setColor(r, g, b, a);
    }

    void drawLine(int x1, int y1, int x2, int y2) const
    {
        io.drawLine(x1, y1, x2, y2);
    }

    void setTarget(Component& c)
    {
        io.setRenderTarget(c);
    }

    void setTarget(const std::unique_ptr<Component>& c)
    {
        io.setRenderTarget(c);
    }

    void drawImage(std::string imageKey, int x, int y) const
    {
        io.renderImage(imageKey, x, y);
    }

private:
    SDL_IO& io;
};

#endif // DRAWING_CONTEXT_H
