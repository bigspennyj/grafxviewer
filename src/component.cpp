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
        if (child.second->needsUpdate())
            child.second->update();
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
