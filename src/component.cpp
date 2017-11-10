#include <iostream>
#include "io.h"
#include "component.h"

void Component::update()
{
    if (needUpdate) {
        redraw();
        needUpdate = false;
    }
}

void ComponentContainer::update()
{
    Component::update();

    for (const auto& child : children) {
        child->update();
    }
}

void MenuComponent::redraw()
{
    std::cout << "REDRAW" << std::endl;
    io.setColor(0xff666666);
    io.drawRectangle(surface, 0, 0, width, height);
    // TODO: move this up to SDL_IO
    io.drawComponent(*this);
}

void Button::redraw()
{
    std::cout << "REDRAW - BUTTON" << std::endl;
    io.setColor(0xff000000);
    io.drawRectangle(surface, 0, 0, width, height);
    // TODO: move this up to SDL_IO
    io.drawComponent(*this);
}
