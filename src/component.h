#ifndef COMPONENT_H
#define COMPONENT_H

#include <vector>
#include <string>
#include <iostream>

#include "io.h"

class Component {
public:
    Component(SDL_IO& ioRef, int x_, int y_, int width_, int height_, SDL_IO::SurfacePointer s) :
        x(x_), y(y_), width(width_), height(height_), needUpdate(true), io(ioRef), surface(std::move(s)) {}

    virtual ~Component() { std::cout << "~COMPONENT" << std::endl; }

    virtual void update();
    virtual void redraw() = 0;

    int X() const noexcept { return x; }
    int Y() const noexcept { return y; }
    int Width() const noexcept { return width; }
    int Height() const noexcept { return height; }
    
    void setX(int x_) noexcept { x = x_; }
    void setY(int y_) noexcept { y = y_; }
    void setWidth(int width_) noexcept { x = width_; }
    void setHeight(int height_) noexcept { x = height_; }
    bool needsUpdate() const noexcept { return needUpdate; }
    void invalidate() noexcept { needUpdate = true; }

    SDL_Surface *surfPointer() const noexcept { return surface.get(); };

protected:
    int x, y, width, height;
    bool needUpdate;

    SDL_IO& io;

    SDL_IO::SurfacePointer surface;
};

class ComponentContainer : public Component {
public:
    ComponentContainer(SDL_IO& ioref, int x_, int y_, int width_, int height_, SDL_IO::SurfacePointer s)
        : Component(ioref, x_, y_, width_, height_, std::move(s)) {}

    virtual ~ComponentContainer() {}

    virtual void update() override;
    virtual void redraw() override {}

    template<typename T>
    void addChild(std::unique_ptr<T> c)
    {
        c->setX(c->X() + x);
        c->setY(c->Y() + y);
        auto child = std::unique_ptr<Component>(dynamic_cast<Component*>(c.release()));
        children.push_back(std::move(child));
    }

protected:
    std::vector<std::unique_ptr<Component>> children;
};

class Button : public Component {
public:
    Button(SDL_IO& ioref, int x_, int y_, int width_, int height_, SDL_IO::SurfacePointer sp) 
        : Component(ioref, x_, y_, width_, height_, std::move(sp)), buttonText()
    {
    }
    virtual ~Button() {}

    virtual void redraw() override;
private:
    std::string buttonText;
};

class MenuComponent : public ComponentContainer {
public:
    MenuComponent(SDL_IO& ioref, int x_, int y_, int width_, int height_, SDL_IO::SurfacePointer sp) 
        : ComponentContainer(ioref, x_, y_, width_, height_, std::move(sp))
    {
    }
    virtual ~MenuComponent() {}

    virtual void redraw() override;
};

#endif //component_h
