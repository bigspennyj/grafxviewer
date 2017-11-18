#ifndef COMPONENT_H
#define COMPONENT_H

#include <vector>
#include <string>
#include <iostream>

#include "drawingcontext.h"

class Component {
public:
    using ClickHandler = std::function<void(const SDL_IO::EventArgs&)>;

    Component(int x_, int y_, int width_, int height_, SDL_IO::SurfacePointer s) :
        x(x_), y(y_), width(width_), height(height_), needUpdate(true), surface(std::move(s)) {}

    virtual ~Component() { }

    virtual void update(DrawingContext& c);
    virtual void redraw(const DrawingContext& c) = 0;
    virtual bool handleEvent(const SDL_IO::EventArgs& e) = 0;

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

    template<typename Callable>
    void setClickHandler(Callable callback)
    {
        onClickCallback = callback;
    }

protected:
    int x, y, width, height;
    bool needUpdate;
    bool AABB(const int x_, const int y_) const noexcept;

    ClickHandler onClickCallback;
    SDL_IO::SurfacePointer surface;

};

class ComponentContainer : public Component {
public:
    ComponentContainer(int x_, int y_, int width_, int height_, SDL_IO::SurfacePointer s)
        : Component(x_, y_, width_, height_, std::move(s)) {}

    virtual ~ComponentContainer() {}

    virtual void update(DrawingContext& c) override;
    virtual void redraw(const DrawingContext&) override {}

    virtual bool handleEvent(const SDL_IO::EventArgs& e) override;

    template<typename T>
    const std::unique_ptr<Component>& addChild(std::unique_ptr<T> c)
    {
        // coords should be relative to the container, so update them
        c->setX(c->X() + x);
        c->setY(c->Y() + y);

        auto child = std::unique_ptr<Component>(dynamic_cast<Component*>(c.release()));
        children.push_back(std::move(child));

        return children.back();
    }
protected:
    std::vector<std::unique_ptr<Component>> children;
    virtual bool handleMouseEvent(const SDL_IO::EventArgs& e);
};

#endif //component_h
