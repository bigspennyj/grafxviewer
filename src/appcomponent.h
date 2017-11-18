#ifndef APP_COMPONENT_H
#define APP_COMPONENT_H

#include "component.h"
#include "drawingcontext.h"
#include "model.h"

class Model;
class Button : public Component {
public:
    Button(int x_, int y_, int width_, int height_, SDL_IO::SurfacePointer sp)
        : Component(x_, y_, width_, height_, std::move(sp)), buttonText(), currentColor(0xff000000), isPressed(false)
    {
    }
    virtual ~Button() {}

    virtual void redraw(const DrawingContext& c) override;
    virtual bool handleEvent(const SDL_IO::EventArgs& e) override;
    void cycleColor() noexcept;

private:
    std::string buttonText;
    long unsigned int currentColor;
    bool isPressed;
};

class MenuComponent : public ComponentContainer {
public:
    MenuComponent(int x_, int y_, int width_, int height_, SDL_IO::SurfacePointer sp)
        : ComponentContainer(x_, y_, width_, height_, std::move(sp))
    {
    }
    virtual ~MenuComponent() {}

    virtual void redraw(const DrawingContext& c) override;
};

class ModelView : public Component {
public:
    ModelView(int x_, int y_, int width_, int height_, const Model& model_,
            SDL_IO::SurfacePointer sp)
        : Component(x_, y_, width_, height_, std::move(sp)), model(model_), unit(height_ / 100)
    {}

    virtual void redraw(const DrawingContext& c) override;
    virtual bool handleEvent(const SDL_IO::EventArgs& e) override { return false; }

private:
    const Model& model;
    double unit;
};

#endif //APP_COMPONENT_H
