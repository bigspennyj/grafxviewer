#ifndef DRAWING_CONTEXT_H
#define DRAWING_CONTEXT_H

#include "io.h"
#include <iostream>

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

    void drawRectangle(int x1, int y1, int x2, int y2) const
    {
        io.drawRectangle(renderer, x1, y1, x2, y2);
    }

    void drawComponent(const Component& c) const
    {
        io.drawComponent(renderer, c);
    }

    void setColor(int r, int g, int b, int a) const
    {
        io.setColor(renderer, r, g, b, a);
    }

    void drawLine(int x1, int y1, int x2, int y2) const
    {
        io.drawLine(renderer, x1, y1, x2, y2);
    }

    void setTarget(Component& c)
    {
    }

    void setTarget(const std::unique_ptr<Component>& c)
    {
    }

    void drawImage(const SDL_IO::SurfacePointer& s, int x, int y, std::string imageKey) const
    {
        io.renderImage(s, imageKey, x, y);
    }

private:
    SDL_IO& io;
    SDL_IO::RendererPointer renderer;
};

#endif // DRAWING_CONTEXT_H
