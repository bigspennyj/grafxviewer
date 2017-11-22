#include <iostream>
#include "drawingcontext.h"
#include "component.h"

//------------------------------------------------------------------------------
// Component functions
//------------------------------------------------------------------------------
void Component::update(DrawingContext& dc)
{
    if (needUpdate) {
        dc.setTarget(*this);
        redraw(dc); //this sets needUpdate on a per-component basis
    }
}

bool Component::AABB(const int x_, const int y_) const noexcept
{
    return (x_ >= x && x_ <= x + width)
        && (y_ >= y && y_ <= y + height);
}

//------------------------------------------------------------------------------
// ComponentContainer functions
//------------------------------------------------------------------------------
void ComponentContainer::update(DrawingContext& c)
{
    Component::update(c);

    for (const auto& child : children) {
        c.setTarget(child);
        child->update(c);
    }
}

bool ComponentContainer::handleEvent(const SDL_IO::EventArgs& e)
{
    for (const auto& child : children) {
        if (child->handleEvent(e))
            return true;
    }
    if (handleMouseEvent(e))
        return true;
    return false;
}



bool ComponentContainer::handleMouseEvent(const SDL_IO::EventArgs& e)
{
    if (AABB(e.x, e.y)) {
        std::cout << "componentcontainer clicked" << std::endl;
        if (onClickCallback)
            onClickCallback(e);
        return true;
    }
    return false;
}

