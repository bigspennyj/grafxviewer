#ifndef COMPONENT_H
#define COMPONENT_H

#include <vector>
#include <string>
#include <iostream>

#include "drawingcontext.h"

class Component {
public:
    using ClickHandler = std::function<void(const SDL_IO::EventArgs&)>;

    Component(int x_, int y_, int width_, int height_, SDL_IO::TexturePointer s) :
        x(x_), y(y_), width(width_), height(height_), needUpdate(true), visible(true), texture(std::move(s)) {}

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
    void invalidate() { needUpdate = true; }

    virtual void setVisible(bool v) noexcept { visible = v; }
    bool isVisible() const noexcept { return visible; }
    SDL_Texture *texturePointer() const noexcept { return texture.get(); };

    // wtf is this?
    template<typename Callable>
    void setClickHandler(Callable callback)
    {
        onClickCallback = callback;
    }

protected:
    int x, y, width, height;
    bool needUpdate;
    bool AABB(const int x_, const int y_) const noexcept;
    bool visible;

    ClickHandler onClickCallback;
    SDL_IO::TexturePointer texture;

};

class ComponentContainer : public Component {
public:
    ComponentContainer(int x_, int y_, int width_, int height_, SDL_IO::TexturePointer s)
        : Component(x_, y_, width_, height_, std::move(s)), children() { children.reserve(10); }

    virtual ~ComponentContainer() {}

    virtual void update(DrawingContext& c) override;
    virtual void redraw(const DrawingContext&) override {}

    virtual bool handleEvent(const SDL_IO::EventArgs& e) override;

    virtual void setVisible(bool v) noexcept override
    {
        visible = v;
        for (auto& component : children) {
            component->setVisible(v);
            component->invalidate();
        }
        invalidate();
    }

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
