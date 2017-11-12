#include <iostream>
#include "drawingcontext.h"
#include "component.h"

void Component::update(const DrawingContext& c)
{
    if (needUpdate) {
        redraw(c);
        needUpdate = false;
    }
}

void ComponentContainer::update(const DrawingContext& c)
{
    Component::update(c);

    for (const auto& child : children) {
        child->update(c);
    }
}

void ComponentContainer::update(DrawingContext&& c)
{
    update(c);
}
void MenuComponent::redraw(const DrawingContext& c)
{
    std::cout << "REDRAW" << std::endl;
    c.setColor(0xff666666);
    c.drawRectangle(surface, 0, 0, width, height);
    c.drawComponent(*this);
}

void Button::redraw(const DrawingContext& c)
{
    std::cout << "REDRAW - BUTTON" << std::endl;
    c.setColor(0xff000000);
    c.drawRectangle(surface, 0, 0, width, height);
    // TODO: move this up to SDL_IO
    c.drawComponent(*this);
}
